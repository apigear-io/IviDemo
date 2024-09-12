/**
Copyright 2021 ApiGear UG
Copyright 2021 Epic Games, Inc.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

////////////////////////////////
// WARNING AUTOGENERATED
// DO NOT MODIFY
///////////////////////////////

#include "Generated/OLink/IviTunerTunerOLinkClient.h"
#include "ApiGearSettings.h"
#include "apigearolink.h"
#include "Async/Async.h"
#include "Generated/api/IviTuner.json.adapter.h"
#include "unrealolink.h"
#include "unrealolinksink.h"
#include "Engine/Engine.h"
#include "ApiGear/Public/ApiGearConnectionsStore.h"
#include "Misc/DateTime.h"
#include "IviTunerSettings.h"
THIRD_PARTY_INCLUDES_START
#include "olink/clientnode.h"
#include "olink/iobjectsink.h"
THIRD_PARTY_INCLUDES_END
#include <atomic>
#include "HAL/CriticalSection.h"

/**
   \brief data structure to hold the last sent property values
*/
struct IviTunerTunerPropertiesData
{
	FCriticalSection CurrentStationMutex;
	FIviTunerStation CurrentStation{FIviTunerStation()};
	FCriticalSection StationsMutex;
	TArray<FIviTunerStation> Stations{TArray<FIviTunerStation>()};
	std::atomic<bool> bAutoScanEnabled{false};
	std::atomic<EIviTunerWaveband> Waveband{EIviTunerWaveband::ITW_AM};
};
DEFINE_LOG_CATEGORY(LogIviTunerTunerOLinkClient);

UIviTunerTunerOLinkClient::UIviTunerTunerOLinkClient()
	: UAbstractIviTunerTuner()
#if (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION < 27)
	, _SentData(MakeUnique<IviTunerTunerPropertiesData>())
#else
	, _SentData(MakePimpl<IviTunerTunerPropertiesData>())
#endif
{
	m_sink = std::make_shared<FUnrealOLinkSink>("ivi.tuner.Tuner");
}

UIviTunerTunerOLinkClient::UIviTunerTunerOLinkClient(FVTableHelper& Helper)
	: Super(Helper)
{
}
UIviTunerTunerOLinkClient::~UIviTunerTunerOLinkClient() = default;

void UIviTunerTunerOLinkClient::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	m_sink->setOnInitCallback([this]()
		{ _SubscriptionStatusChanged.Broadcast(true); });
	m_sink->setOnReleaseCallback([this]()
		{ _SubscriptionStatusChanged.Broadcast(false); });

	FUnrealOLinkSink::FPropertyChangedFunc PropertyChangedFunc = [this](const nlohmann::json& props)
	{
		this->applyState(props);
	};
	m_sink->setOnPropertyChangedCallback(PropertyChangedFunc);

	FUnrealOLinkSink::FSignalEmittedFunc SignalEmittedFunc = [this](const std::string& signalName, const nlohmann::json& args)
	{
		this->emitSignal(signalName, args);
	};
	m_sink->setOnSignalEmittedCallback(SignalEmittedFunc);

	check(GEngine);
	UIviTunerSettings* settings = GetMutableDefault<UIviTunerSettings>();

	UApiGearConnectionsStore* AGCM = GEngine->GetEngineSubsystem<UApiGearConnectionsStore>();

	TScriptInterface<IApiGearConnection> OLinkConnection = AGCM->GetConnection(settings->OLinkConnectionIdentifier);

	if (!OLinkConnection.GetInterface())
	{
		UE_LOG(LogIviTunerTunerOLinkClient, Warning, TEXT("No valid olink connection for the %s client, please set in the ApiGear IviTuner plugin settings or during run time"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		return;
	}
	UseConnection(OLinkConnection);
	OLinkConnection->Connect();
}

void UIviTunerTunerOLinkClient::Deinitialize()
{
	// tell the sink that we are gone and should not try to be invoked
	m_sink->resetOnPropertyChangedCallback();
	m_sink->resetOnSignalEmittedCallback();
	m_sink->resetOnInitCallback();
	m_sink->resetOnReleaseCallback();

	if (Connection.GetObject())
	{
		UUnrealOLink* UnrealOLinkConnection = Cast<UUnrealOLink>(Connection.GetObject());
		UnrealOLinkConnection->unlinkObjectSource(m_sink->olinkObjectName());
		UnrealOLinkConnection->node()->registry().removeSink(m_sink->olinkObjectName());
	}

	Super::Deinitialize();
}

void UIviTunerTunerOLinkClient::UseConnection(TScriptInterface<IApiGearConnection> InConnection)
{
	checkf(InConnection.GetInterface() != nullptr, TEXT("Cannot use connection - interface IApiGearConnection is not fully implemented"));

	// only accept connections of type olink
	checkf(InConnection->GetConnectionProtocolIdentifier() == ApiGearOLinkProtocolIdentifier, TEXT("Cannot use connection - must be of type olink"));

	UUnrealOLink* UnrealOLinkConnection = nullptr;
	// remove old connection
	if (Connection.GetObject())
	{
		UnrealOLinkConnection = Cast<UUnrealOLink>(Connection.GetObject());
		UnrealOLinkConnection->unlinkObjectSource(m_sink->olinkObjectName());
		UnrealOLinkConnection->node()->registry().removeSink(m_sink->olinkObjectName());
		UnrealOLinkConnection = nullptr;
	}

	// set up new connection
	UnrealOLinkConnection = Cast<UUnrealOLink>(InConnection.GetObject());
	UnrealOLinkConnection->node()->registry().addSink(m_sink);
	UnrealOLinkConnection->linkObjectSource(m_sink->olinkObjectName());

	Connection = InConnection;
}

FIviTunerStation UIviTunerTunerOLinkClient::GetCurrentStation_Implementation() const
{
	return CurrentStation;
}

void UIviTunerTunerOLinkClient::SetCurrentStation_Implementation(const FIviTunerStation& InCurrentStation)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogIviTunerTunerOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		return;
	}

	// only send change requests if the value changed -> reduce network load
	if (GetCurrentStation_Implementation() == InCurrentStation)
	{
		return;
	}

	// only send change requests if the value wasn't already sent -> reduce network load
	{
		FScopeLock Lock(&(_SentData->CurrentStationMutex));
		if (_SentData->CurrentStation == InCurrentStation)
		{
			return;
		}
	}
	static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "currentStation");
	m_sink->GetNode()->setRemoteProperty(memberId, InCurrentStation);
	FScopeLock Lock(&(_SentData->CurrentStationMutex));
	_SentData->CurrentStation = InCurrentStation;
}

TArray<FIviTunerStation> UIviTunerTunerOLinkClient::GetStations_Implementation() const
{
	return Stations;
}

void UIviTunerTunerOLinkClient::SetStations_Implementation(const TArray<FIviTunerStation>& InStations)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogIviTunerTunerOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		return;
	}

	// only send change requests if the value changed -> reduce network load
	if (GetStations_Implementation() == InStations)
	{
		return;
	}

	// only send change requests if the value wasn't already sent -> reduce network load
	{
		FScopeLock Lock(&(_SentData->StationsMutex));
		if (_SentData->Stations == InStations)
		{
			return;
		}
	}
	static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "stations");
	m_sink->GetNode()->setRemoteProperty(memberId, InStations);
	FScopeLock Lock(&(_SentData->StationsMutex));
	_SentData->Stations = InStations;
}

bool UIviTunerTunerOLinkClient::GetAutoScanEnabled_Implementation() const
{
	return bAutoScanEnabled;
}

void UIviTunerTunerOLinkClient::SetAutoScanEnabled_Implementation(bool bInAutoScanEnabled)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogIviTunerTunerOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		return;
	}

	// only send change requests if the value changed -> reduce network load
	if (GetAutoScanEnabled_Implementation() == bInAutoScanEnabled)
	{
		return;
	}

	// only send change requests if the value wasn't already sent -> reduce network load
	if (_SentData->bAutoScanEnabled == bInAutoScanEnabled)
	{
		return;
	}
	static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "autoScanEnabled");
	m_sink->GetNode()->setRemoteProperty(memberId, bInAutoScanEnabled);
	_SentData->bAutoScanEnabled = bInAutoScanEnabled;
}

EIviTunerWaveband UIviTunerTunerOLinkClient::GetWaveband_Implementation() const
{
	return Waveband;
}

void UIviTunerTunerOLinkClient::SetWaveband_Implementation(EIviTunerWaveband InWaveband)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogIviTunerTunerOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		return;
	}

	// only send change requests if the value changed -> reduce network load
	if (GetWaveband_Implementation() == InWaveband)
	{
		return;
	}

	// only send change requests if the value wasn't already sent -> reduce network load
	if (_SentData->Waveband == InWaveband)
	{
		return;
	}
	static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "waveband");
	m_sink->GetNode()->setRemoteProperty(memberId, InWaveband);
	_SentData->Waveband = InWaveband;
}

void UIviTunerTunerOLinkClient::ScanStations_Implementation(EIviTunerWaveband Band)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogIviTunerTunerOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));

		return;
	}
	ApiGear::ObjectLink::InvokeReplyFunc GetTunerStateFunc = [this](ApiGear::ObjectLink::InvokeReplyArg arg) {};
	static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "scanStations");
	m_sink->GetNode()->invokeRemote(memberId, {Band}, GetTunerStateFunc);
}

void UIviTunerTunerOLinkClient::AutoScan_Implementation(EIviTunerWaveband Band)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogIviTunerTunerOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));

		return;
	}
	ApiGear::ObjectLink::InvokeReplyFunc GetTunerStateFunc = [this](ApiGear::ObjectLink::InvokeReplyArg arg) {};
	static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "autoScan");
	m_sink->GetNode()->invokeRemote(memberId, {Band}, GetTunerStateFunc);
}

void UIviTunerTunerOLinkClient::NextStation_Implementation()
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogIviTunerTunerOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));

		return;
	}
	ApiGear::ObjectLink::InvokeReplyFunc GetTunerStateFunc = [this](ApiGear::ObjectLink::InvokeReplyArg arg) {};
	static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "nextStation");
	m_sink->GetNode()->invokeRemote(memberId, {}, GetTunerStateFunc);
}

void UIviTunerTunerOLinkClient::PreviousStation_Implementation()
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogIviTunerTunerOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));

		return;
	}
	ApiGear::ObjectLink::InvokeReplyFunc GetTunerStateFunc = [this](ApiGear::ObjectLink::InvokeReplyArg arg) {};
	static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "previousStation");
	m_sink->GetNode()->invokeRemote(memberId, {}, GetTunerStateFunc);
}

bool UIviTunerTunerOLinkClient::_IsSubscribed() const
{
	return m_sink->IsReady();
}

void UIviTunerTunerOLinkClient::applyState(const nlohmann::json& fields)
{
	const bool bCurrentStationChanged = fields.contains("currentStation") && (CurrentStation != fields["currentStation"].get<FIviTunerStation>());
	if (bCurrentStationChanged)
	{
		CurrentStation = fields["currentStation"].get<FIviTunerStation>();
		Execute__GetSignals(this)->OnCurrentStationChanged.Broadcast(CurrentStation);
	}

	const bool bStationsChanged = fields.contains("stations") && (Stations != fields["stations"].get<TArray<FIviTunerStation>>());
	if (bStationsChanged)
	{
		Stations = fields["stations"].get<TArray<FIviTunerStation>>();
		Execute__GetSignals(this)->OnStationsChanged.Broadcast(Stations);
	}

	const bool bAutoScanEnabledChanged = fields.contains("autoScanEnabled") && (bAutoScanEnabled != fields["autoScanEnabled"].get<bool>());
	if (bAutoScanEnabledChanged)
	{
		bAutoScanEnabled = fields["autoScanEnabled"].get<bool>();
		Execute__GetSignals(this)->OnAutoScanEnabledChanged.Broadcast(bAutoScanEnabled);
	}

	const bool bWavebandChanged = fields.contains("waveband") && (Waveband != fields["waveband"].get<EIviTunerWaveband>());
	if (bWavebandChanged)
	{
		Waveband = fields["waveband"].get<EIviTunerWaveband>();
		Execute__GetSignals(this)->OnWavebandChanged.Broadcast(Waveband);
	}
}

void UIviTunerTunerOLinkClient::emitSignal(const std::string& signalName, const nlohmann::json& args)
{
}
