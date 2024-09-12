
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
#include "Generated/Monitor/IviTunerTunerLoggingDecorator.h"
#include "IviTuner.trace.h"
#include "IviTunerFactory.h"
#include "Runtime/Launch/Resources/Version.h"

DEFINE_LOG_CATEGORY(LogIviTunerTunerLoggingDecorator);
UIviTunerTunerLoggingDecorator::UIviTunerTunerLoggingDecorator()
	: UAbstractIviTunerTuner()
{
}

UIviTunerTunerLoggingDecorator::~UIviTunerTunerLoggingDecorator() = default;

void UIviTunerTunerLoggingDecorator::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
#if (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION < 27)
	setBackendService(FIviTunerModuleFactory::createIIviTunerTunerInterface(GetGameInstance(), Collection));
#else
	setBackendService(FIviTunerModuleFactory::createIIviTunerTunerInterface(Collection));
#endif
}

void UIviTunerTunerLoggingDecorator::Deinitialize()
{
	Super::Deinitialize();
	BackendService = nullptr;
}

void UIviTunerTunerLoggingDecorator::setBackendService(TScriptInterface<IIviTunerTunerInterface> InService)
{
	// unsubscribe from old backend
	if (BackendService != nullptr)
	{
		UIviTunerTunerSignals* BackendSignals = BackendService->Execute__GetSignals(BackendService.GetObject());
		checkf(BackendSignals, TEXT("Cannot unsubscribe from delegates from backend service IviTunerTuner"));
		BackendSignals->OnCurrentStationChanged.RemoveDynamic(this, &UIviTunerTunerLoggingDecorator::OnCurrentStationChanged);
		BackendSignals->OnStationsChanged.RemoveDynamic(this, &UIviTunerTunerLoggingDecorator::OnStationsChanged);
		BackendSignals->OnAutoScanEnabledChanged.RemoveDynamic(this, &UIviTunerTunerLoggingDecorator::OnAutoScanEnabledChanged);
		BackendSignals->OnWavebandChanged.RemoveDynamic(this, &UIviTunerTunerLoggingDecorator::OnWavebandChanged);
	}

	// only set if interface is implemented
	checkf(InService.GetInterface() != nullptr, TEXT("Cannot set backend service - interface IviTunerTuner is not fully implemented"));

	// subscribe to new backend
	BackendService = InService;
	UIviTunerTunerSignals* BackendSignals = BackendService->Execute__GetSignals(BackendService.GetObject());
	checkf(BackendSignals, TEXT("Cannot unsubscribe from delegates from backend service IviTunerTuner"));
	// connect property changed signals or simple events
	BackendSignals->OnCurrentStationChanged.AddDynamic(this, &UIviTunerTunerLoggingDecorator::OnCurrentStationChanged);
	BackendSignals->OnStationsChanged.AddDynamic(this, &UIviTunerTunerLoggingDecorator::OnStationsChanged);
	BackendSignals->OnAutoScanEnabledChanged.AddDynamic(this, &UIviTunerTunerLoggingDecorator::OnAutoScanEnabledChanged);
	BackendSignals->OnWavebandChanged.AddDynamic(this, &UIviTunerTunerLoggingDecorator::OnWavebandChanged);
	// populate service state to proxy
	CurrentStation = BackendService->Execute_GetCurrentStation(BackendService.GetObject());
	Stations = BackendService->Execute_GetStations(BackendService.GetObject());
	bAutoScanEnabled = BackendService->Execute_GetAutoScanEnabled(BackendService.GetObject());
	Waveband = BackendService->Execute_GetWaveband(BackendService.GetObject());
}

void UIviTunerTunerLoggingDecorator::OnCurrentStationChanged(const FIviTunerStation& InCurrentStation)
{
	IviTunerTunerTracer::capture_state(BackendService.GetObject(), this);
	CurrentStation = InCurrentStation;
	Execute__GetSignals(this)->OnCurrentStationChanged.Broadcast(InCurrentStation);
}

FIviTunerStation UIviTunerTunerLoggingDecorator::GetCurrentStation_Implementation() const
{
	return BackendService->Execute_GetCurrentStation(BackendService.GetObject());
}

void UIviTunerTunerLoggingDecorator::SetCurrentStation_Implementation(const FIviTunerStation& InCurrentStation)
{
	IviTunerTunerTracer::trace_callSetCurrentStation(InCurrentStation);
	BackendService->Execute_SetCurrentStation(BackendService.GetObject(), InCurrentStation);
}

void UIviTunerTunerLoggingDecorator::OnStationsChanged(const TArray<FIviTunerStation>& InStations)
{
	IviTunerTunerTracer::capture_state(BackendService.GetObject(), this);
	Stations = InStations;
	Execute__GetSignals(this)->OnStationsChanged.Broadcast(InStations);
}

TArray<FIviTunerStation> UIviTunerTunerLoggingDecorator::GetStations_Implementation() const
{
	return BackendService->Execute_GetStations(BackendService.GetObject());
}

void UIviTunerTunerLoggingDecorator::SetStations_Implementation(const TArray<FIviTunerStation>& InStations)
{
	IviTunerTunerTracer::trace_callSetStations(InStations);
	BackendService->Execute_SetStations(BackendService.GetObject(), InStations);
}

void UIviTunerTunerLoggingDecorator::OnAutoScanEnabledChanged(bool bInAutoScanEnabled)
{
	IviTunerTunerTracer::capture_state(BackendService.GetObject(), this);
	bAutoScanEnabled = bInAutoScanEnabled;
	Execute__GetSignals(this)->OnAutoScanEnabledChanged.Broadcast(bInAutoScanEnabled);
}

bool UIviTunerTunerLoggingDecorator::GetAutoScanEnabled_Implementation() const
{
	return BackendService->Execute_GetAutoScanEnabled(BackendService.GetObject());
}

void UIviTunerTunerLoggingDecorator::SetAutoScanEnabled_Implementation(bool bInAutoScanEnabled)
{
	IviTunerTunerTracer::trace_callSetAutoScanEnabled(bInAutoScanEnabled);
	BackendService->Execute_SetAutoScanEnabled(BackendService.GetObject(), bInAutoScanEnabled);
}

void UIviTunerTunerLoggingDecorator::OnWavebandChanged(EIviTunerWaveband InWaveband)
{
	IviTunerTunerTracer::capture_state(BackendService.GetObject(), this);
	Waveband = InWaveband;
	Execute__GetSignals(this)->OnWavebandChanged.Broadcast(InWaveband);
}

EIviTunerWaveband UIviTunerTunerLoggingDecorator::GetWaveband_Implementation() const
{
	return BackendService->Execute_GetWaveband(BackendService.GetObject());
}

void UIviTunerTunerLoggingDecorator::SetWaveband_Implementation(EIviTunerWaveband InWaveband)
{
	IviTunerTunerTracer::trace_callSetWaveband(InWaveband);
	BackendService->Execute_SetWaveband(BackendService.GetObject(), InWaveband);
}

void UIviTunerTunerLoggingDecorator::ScanStations_Implementation(EIviTunerWaveband Band)
{
	IviTunerTunerTracer::trace_callScanStations(Band);
	BackendService->Execute_ScanStations(BackendService.GetObject(), Band);
}

void UIviTunerTunerLoggingDecorator::AutoScan_Implementation(EIviTunerWaveband Band)
{
	IviTunerTunerTracer::trace_callAutoScan(Band);
	BackendService->Execute_AutoScan(BackendService.GetObject(), Band);
}

void UIviTunerTunerLoggingDecorator::NextStation_Implementation()
{
	IviTunerTunerTracer::trace_callNextStation();
	BackendService->Execute_NextStation(BackendService.GetObject());
}

void UIviTunerTunerLoggingDecorator::PreviousStation_Implementation()
{
	IviTunerTunerTracer::trace_callPreviousStation();
	BackendService->Execute_PreviousStation(BackendService.GetObject());
}
