
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
#include "Generated/Monitor/IviTunerGeneralLoggingDecorator.h"
#include "IviTuner.trace.h"
#include "IviTunerFactory.h"
#include "Runtime/Launch/Resources/Version.h"

DEFINE_LOG_CATEGORY(LogIviTunerGeneralLoggingDecorator);
UIviTunerGeneralLoggingDecorator::UIviTunerGeneralLoggingDecorator()
	: UAbstractIviTunerGeneral()
{
}

UIviTunerGeneralLoggingDecorator::~UIviTunerGeneralLoggingDecorator() = default;

void UIviTunerGeneralLoggingDecorator::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
#if (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION < 27)
	setBackendService(FIviTunerModuleFactory::createIIviTunerGeneralInterface(GetGameInstance(), Collection));
#else
	setBackendService(FIviTunerModuleFactory::createIIviTunerGeneralInterface(Collection));
#endif
}

void UIviTunerGeneralLoggingDecorator::Deinitialize()
{
	Super::Deinitialize();
	BackendService = nullptr;
}

void UIviTunerGeneralLoggingDecorator::setBackendService(TScriptInterface<IIviTunerGeneralInterface> InService)
{
	// unsubscribe from old backend
	if (BackendService != nullptr)
	{
		UIviTunerGeneralSignals* BackendSignals = BackendService->Execute__GetSignals(BackendService.GetObject());
		checkf(BackendSignals, TEXT("Cannot unsubscribe from delegates from backend service IviTunerGeneral"));
		BackendSignals->OnAutoScanIntervalChanged.RemoveDynamic(this, &UIviTunerGeneralLoggingDecorator::OnAutoScanIntervalChanged);
		BackendSignals->OnFavoritesSizeChanged.RemoveDynamic(this, &UIviTunerGeneralLoggingDecorator::OnFavoritesSizeChanged);
	}

	// only set if interface is implemented
	checkf(InService.GetInterface() != nullptr, TEXT("Cannot set backend service - interface IviTunerGeneral is not fully implemented"));

	// subscribe to new backend
	BackendService = InService;
	UIviTunerGeneralSignals* BackendSignals = BackendService->Execute__GetSignals(BackendService.GetObject());
	checkf(BackendSignals, TEXT("Cannot unsubscribe from delegates from backend service IviTunerGeneral"));
	// connect property changed signals or simple events
	BackendSignals->OnAutoScanIntervalChanged.AddDynamic(this, &UIviTunerGeneralLoggingDecorator::OnAutoScanIntervalChanged);
	BackendSignals->OnFavoritesSizeChanged.AddDynamic(this, &UIviTunerGeneralLoggingDecorator::OnFavoritesSizeChanged);
	// populate service state to proxy
	AutoScanInterval = BackendService->Execute_GetAutoScanInterval(BackendService.GetObject());
	FavoritesSize = BackendService->Execute_GetFavoritesSize(BackendService.GetObject());
}

void UIviTunerGeneralLoggingDecorator::OnAutoScanIntervalChanged(int32 InAutoScanInterval)
{
	IviTunerGeneralTracer::capture_state(BackendService.GetObject(), this);
	AutoScanInterval = InAutoScanInterval;
	Execute__GetSignals(this)->OnAutoScanIntervalChanged.Broadcast(InAutoScanInterval);
}

int32 UIviTunerGeneralLoggingDecorator::GetAutoScanInterval_Implementation() const
{
	return BackendService->Execute_GetAutoScanInterval(BackendService.GetObject());
}

void UIviTunerGeneralLoggingDecorator::SetAutoScanInterval_Implementation(int32 InAutoScanInterval)
{
	IviTunerGeneralTracer::trace_callSetAutoScanInterval(InAutoScanInterval);
	BackendService->Execute_SetAutoScanInterval(BackendService.GetObject(), InAutoScanInterval);
}

void UIviTunerGeneralLoggingDecorator::OnFavoritesSizeChanged(const FIviTunerGridSize& InFavoritesSize)
{
	IviTunerGeneralTracer::capture_state(BackendService.GetObject(), this);
	FavoritesSize = InFavoritesSize;
	Execute__GetSignals(this)->OnFavoritesSizeChanged.Broadcast(InFavoritesSize);
}

FIviTunerGridSize UIviTunerGeneralLoggingDecorator::GetFavoritesSize_Implementation() const
{
	return BackendService->Execute_GetFavoritesSize(BackendService.GetObject());
}

void UIviTunerGeneralLoggingDecorator::SetFavoritesSize_Implementation(const FIviTunerGridSize& InFavoritesSize)
{
	IviTunerGeneralTracer::trace_callSetFavoritesSize(InFavoritesSize);
	BackendService->Execute_SetFavoritesSize(BackendService.GetObject(), InFavoritesSize);
}
