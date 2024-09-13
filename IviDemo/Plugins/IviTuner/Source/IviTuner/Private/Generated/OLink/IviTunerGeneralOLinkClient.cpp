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

#include "Generated/OLink/IviTunerGeneralOLinkClient.h"
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
struct IviTunerGeneralPropertiesData
{
	std::atomic<int32> AutoScanInterval{0};
	FCriticalSection FavoritesSizeMutex;
	FIviTunerGridSize FavoritesSize{FIviTunerGridSize()};
};
DEFINE_LOG_CATEGORY(LogIviTunerGeneralOLinkClient);

UIviTunerGeneralOLinkClient::UIviTunerGeneralOLinkClient()
	: UAbstractIviTunerGeneral()
#if (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION < 27)
	, _SentData(MakeUnique<IviTunerGeneralPropertiesData>())
#else
	, _SentData(MakePimpl<IviTunerGeneralPropertiesData>())
#endif
{
	m_sink = std::make_shared<FUnrealOLinkSink>("ivi.tuner.General");
}

UIviTunerGeneralOLinkClient::UIviTunerGeneralOLinkClient(FVTableHelper& Helper)
	: Super(Helper)
{
}
UIviTunerGeneralOLinkClient::~UIviTunerGeneralOLinkClient() = default;

void UIviTunerGeneralOLinkClient::Initialize(FSubsystemCollectionBase& Collection)
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
		UE_LOG(LogIviTunerGeneralOLinkClient, Warning, TEXT("No valid olink connection for the %s client, please set in the ApiGear IviTuner plugin settings or during run time"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		return;
	}
	UseConnection(OLinkConnection);
	OLinkConnection->Connect();
}

void UIviTunerGeneralOLinkClient::Deinitialize()
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

void UIviTunerGeneralOLinkClient::UseConnection(TScriptInterface<IApiGearConnection> InConnection)
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

int32 UIviTunerGeneralOLinkClient::GetAutoScanInterval_Implementation() const
{
	return AutoScanInterval;
}

void UIviTunerGeneralOLinkClient::SetAutoScanInterval_Implementation(int32 InAutoScanInterval)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogIviTunerGeneralOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		return;
	}

	// only send change requests if the value changed -> reduce network load
	if (GetAutoScanInterval_Implementation() == InAutoScanInterval)
	{
		return;
	}

	// only send change requests if the value wasn't already sent -> reduce network load
	if (_SentData->AutoScanInterval == InAutoScanInterval)
	{
		return;
	}
	static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "autoScanInterval");
	m_sink->GetNode()->setRemoteProperty(memberId, InAutoScanInterval);
	_SentData->AutoScanInterval = InAutoScanInterval;
}

FIviTunerGridSize UIviTunerGeneralOLinkClient::GetFavoritesSize_Implementation() const
{
	return FavoritesSize;
}

void UIviTunerGeneralOLinkClient::SetFavoritesSize_Implementation(const FIviTunerGridSize& InFavoritesSize)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogIviTunerGeneralOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		return;
	}

	// only send change requests if the value changed -> reduce network load
	if (GetFavoritesSize_Implementation() == InFavoritesSize)
	{
		return;
	}

	// only send change requests if the value wasn't already sent -> reduce network load
	{
		FScopeLock Lock(&(_SentData->FavoritesSizeMutex));
		if (_SentData->FavoritesSize == InFavoritesSize)
		{
			return;
		}
	}
	static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "favoritesSize");
	m_sink->GetNode()->setRemoteProperty(memberId, InFavoritesSize);
	FScopeLock Lock(&(_SentData->FavoritesSizeMutex));
	_SentData->FavoritesSize = InFavoritesSize;
}

bool UIviTunerGeneralOLinkClient::_IsSubscribed() const
{
	return m_sink->IsReady();
}

void UIviTunerGeneralOLinkClient::applyState(const nlohmann::json& fields)
{
	const bool bAutoScanIntervalChanged = fields.contains("autoScanInterval") && (AutoScanInterval != fields["autoScanInterval"].get<int32>());
	if (bAutoScanIntervalChanged)
	{
		AutoScanInterval = fields["autoScanInterval"].get<int32>();
		Execute__GetSignals(this)->OnAutoScanIntervalChanged.Broadcast(AutoScanInterval);
	}

	const bool bFavoritesSizeChanged = fields.contains("favoritesSize") && (FavoritesSize != fields["favoritesSize"].get<FIviTunerGridSize>());
	if (bFavoritesSizeChanged)
	{
		FavoritesSize = fields["favoritesSize"].get<FIviTunerGridSize>();
		Execute__GetSignals(this)->OnFavoritesSizeChanged.Broadcast(FavoritesSize);
	}
}

void UIviTunerGeneralOLinkClient::emitSignal(const std::string& signalName, const nlohmann::json& args)
{
}
