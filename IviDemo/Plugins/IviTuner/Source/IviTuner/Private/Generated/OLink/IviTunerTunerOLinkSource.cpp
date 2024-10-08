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

#include "IviTunerTunerOLinkSource.h"
#include "Async/Future.h"
#include "Async/Async.h"
#include "Generated/api/IviTuner.json.adapter.h"
#include "unrealolink.h"
#include "Async/Async.h"
#include "Engine/Engine.h"
#include "Misc/DateTime.h"
THIRD_PARTY_INCLUDES_START
#include "olink/iobjectsource.h"
THIRD_PARTY_INCLUDES_END

using namespace ApiGear::ObjectLink;

namespace
{
static const std::string IviTunerTunerIdentifier{"ivi.tuner.Tuner"};
}

DEFINE_LOG_CATEGORY(LogIviTunerTunerOLinkSource);
IviTunerTunerOLinkSource::IviTunerTunerOLinkSource()
	: Host(nullptr)
{
}

void IviTunerTunerOLinkSource::setBackendService(TScriptInterface<IIviTunerTunerInterface> InService)
{
	// only set if interface is implemented
	if (InService.GetInterface() == nullptr)
	{
		UE_LOG(LogIviTunerTunerOLinkSource, Error, TEXT("Cannot set backend service to %s - interface IviTunerTuner is not fully implemented"), *InService.GetObject()->GetName());
		return;
	}

	BackendService = InService;
}
void IviTunerTunerOLinkSource::OnCurrentStationChanged(const FIviTunerStation& InCurrentStation)
{
	static const auto& propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "currentStation");
	static const auto& objectId = ApiGear::ObjectLink::Name::getObjectId(propertyId);
	for (auto node : Host->GetOLinkRegistry()->getNodes(objectId))
	{
		auto lockedNode = node.lock();
		if (lockedNode)
		{
			lockedNode->notifyPropertyChange(propertyId, InCurrentStation);
		}
	}
}

void IviTunerTunerOLinkSource::OnStationsChanged(const TArray<FIviTunerStation>& InStations)
{
	static const auto& propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "stations");
	static const auto& objectId = ApiGear::ObjectLink::Name::getObjectId(propertyId);
	for (auto node : Host->GetOLinkRegistry()->getNodes(objectId))
	{
		auto lockedNode = node.lock();
		if (lockedNode)
		{
			lockedNode->notifyPropertyChange(propertyId, InStations);
		}
	}
}

void IviTunerTunerOLinkSource::OnAutoScanEnabledChanged(bool bInAutoScanEnabled)
{
	static const auto& propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "autoScanEnabled");
	static const auto& objectId = ApiGear::ObjectLink::Name::getObjectId(propertyId);
	for (auto node : Host->GetOLinkRegistry()->getNodes(objectId))
	{
		auto lockedNode = node.lock();
		if (lockedNode)
		{
			lockedNode->notifyPropertyChange(propertyId, bInAutoScanEnabled);
		}
	}
}

void IviTunerTunerOLinkSource::OnWavebandChanged(EIviTunerWaveband InWaveband)
{
	static const auto& propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "waveband");
	static const auto& objectId = ApiGear::ObjectLink::Name::getObjectId(propertyId);
	for (auto node : Host->GetOLinkRegistry()->getNodes(objectId))
	{
		auto lockedNode = node.lock();
		if (lockedNode)
		{
			lockedNode->notifyPropertyChange(propertyId, InWaveband);
		}
	}
}

void IviTunerTunerOLinkSource::setOLinkHost(TSoftObjectPtr<UUnrealOLinkHost> InHost)
{
	Host = InHost.Get();
}

//
// IObjectSource interface
//

std::string IviTunerTunerOLinkSource::olinkObjectName()
{
	return IviTunerTunerIdentifier;
}

nlohmann::json IviTunerTunerOLinkSource::olinkInvoke(const std::string& methodId, const nlohmann::json& args)
{
	if (!BackendService)
	{
		UE_LOG(LogIviTunerTunerOLinkSource, Error, TEXT("No backend service set - please specify a service in the adapter IviTunerTunerOLinkAdapter which implements the IviTunerTuner interface"));
		return nlohmann::json();
	}

	const std::string path = Name::getMemberName(methodId);
	if (path == "scanStations")
	{
		BackendService->Execute_ScanStations(BackendService.GetObject());
		return nlohmann::json{};
	}
	if (path == "autoScan")
	{
		BackendService->Execute_AutoScan(BackendService.GetObject());
		return nlohmann::json{};
	}
	if (path == "nextStation")
	{
		BackendService->Execute_NextStation(BackendService.GetObject());
		return nlohmann::json{};
	}
	if (path == "previousStation")
	{
		BackendService->Execute_PreviousStation(BackendService.GetObject());
		return nlohmann::json{};
	}
	return nlohmann::json();
}

void IviTunerTunerOLinkSource::olinkSetProperty(const std::string& propertyId, const nlohmann::json& value)
{
	if (!BackendService)
	{
		UE_LOG(LogIviTunerTunerOLinkSource, Error, TEXT("No backend service set - please specify a service in the adapter IviTunerTunerOLinkAdapter which implements the IviTunerTuner interface"));
		return;
	}

	const std::string path = Name::getMemberName(propertyId);
	if (path == "currentStation")
	{
		FIviTunerStation CurrentStation = value.get<FIviTunerStation>();
		BackendService->Execute_SetCurrentStation(BackendService.GetObject(), CurrentStation);
	}
	if (path == "stations")
	{
		TArray<FIviTunerStation> Stations = value.get<TArray<FIviTunerStation>>();
		BackendService->Execute_SetStations(BackendService.GetObject(), Stations);
	}
	if (path == "autoScanEnabled")
	{
		bool bAutoScanEnabled = value.get<bool>();
		BackendService->Execute_SetAutoScanEnabled(BackendService.GetObject(), bAutoScanEnabled);
	}
	if (path == "waveband")
	{
		EIviTunerWaveband Waveband = value.get<EIviTunerWaveband>();
		BackendService->Execute_SetWaveband(BackendService.GetObject(), Waveband);
	}
}

nlohmann::json IviTunerTunerOLinkSource::olinkCollectProperties()
{
	if (!BackendService)
	{
		UE_LOG(LogIviTunerTunerOLinkSource, Error, TEXT("No backend service set - please specify a service in the adapter IviTunerTunerOLinkAdapter which implements the IviTunerTuner interface"));
		return nlohmann::json();
	}

	return nlohmann::json::object({

		{"currentStation", BackendService->Execute_GetCurrentStation(BackendService.GetObject())},
		{"stations", BackendService->Execute_GetStations(BackendService.GetObject())},
		{"autoScanEnabled", BackendService->Execute_GetAutoScanEnabled(BackendService.GetObject())},
		{"waveband", BackendService->Execute_GetWaveband(BackendService.GetObject())}});
}
