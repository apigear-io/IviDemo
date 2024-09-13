
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
#include "Generated/Monitor/IviTunerPreferencesLoggingDecorator.h"
#include "IviTuner.trace.h"
#include "IviTunerFactory.h"
#include "Runtime/Launch/Resources/Version.h"

DEFINE_LOG_CATEGORY(LogIviTunerPreferencesLoggingDecorator);
UIviTunerPreferencesLoggingDecorator::UIviTunerPreferencesLoggingDecorator()
	: UAbstractIviTunerPreferences()
{
}

UIviTunerPreferencesLoggingDecorator::~UIviTunerPreferencesLoggingDecorator() = default;

void UIviTunerPreferencesLoggingDecorator::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
#if (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION < 27)
	setBackendService(FIviTunerModuleFactory::createIIviTunerPreferencesInterface(GetGameInstance(), Collection));
#else
	setBackendService(FIviTunerModuleFactory::createIIviTunerPreferencesInterface(Collection));
#endif
}

void UIviTunerPreferencesLoggingDecorator::Deinitialize()
{
	Super::Deinitialize();
	BackendService = nullptr;
}

void UIviTunerPreferencesLoggingDecorator::setBackendService(TScriptInterface<IIviTunerPreferencesInterface> InService)
{
	// unsubscribe from old backend
	if (BackendService != nullptr)
	{
		UIviTunerPreferencesSignals* BackendSignals = BackendService->Execute__GetSignals(BackendService.GetObject());
		checkf(BackendSignals, TEXT("Cannot unsubscribe from delegates from backend service IviTunerPreferences"));
		BackendSignals->OnAutoScanIntervalChanged.RemoveDynamic(this, &UIviTunerPreferencesLoggingDecorator::OnAutoScanIntervalChanged);
		BackendSignals->OnFavoritesSizeChanged.RemoveDynamic(this, &UIviTunerPreferencesLoggingDecorator::OnFavoritesSizeChanged);
	}

	// only set if interface is implemented
	checkf(InService.GetInterface() != nullptr, TEXT("Cannot set backend service - interface IviTunerPreferences is not fully implemented"));

	// subscribe to new backend
	BackendService = InService;
	UIviTunerPreferencesSignals* BackendSignals = BackendService->Execute__GetSignals(BackendService.GetObject());
	checkf(BackendSignals, TEXT("Cannot unsubscribe from delegates from backend service IviTunerPreferences"));
	// connect property changed signals or simple events
	BackendSignals->OnAutoScanIntervalChanged.AddDynamic(this, &UIviTunerPreferencesLoggingDecorator::OnAutoScanIntervalChanged);
	BackendSignals->OnFavoritesSizeChanged.AddDynamic(this, &UIviTunerPreferencesLoggingDecorator::OnFavoritesSizeChanged);
	// populate service state to proxy
	AutoScanInterval = BackendService->Execute_GetAutoScanInterval(BackendService.GetObject());
	FavoritesSize = BackendService->Execute_GetFavoritesSize(BackendService.GetObject());
}

void UIviTunerPreferencesLoggingDecorator::OnAutoScanIntervalChanged(int32 InAutoScanInterval)
{
	IviTunerPreferencesTracer::capture_state(BackendService.GetObject(), this);
	AutoScanInterval = InAutoScanInterval;
	Execute__GetSignals(this)->OnAutoScanIntervalChanged.Broadcast(InAutoScanInterval);
}

int32 UIviTunerPreferencesLoggingDecorator::GetAutoScanInterval_Implementation() const
{
	return BackendService->Execute_GetAutoScanInterval(BackendService.GetObject());
}

void UIviTunerPreferencesLoggingDecorator::SetAutoScanInterval_Implementation(int32 InAutoScanInterval)
{
	IviTunerPreferencesTracer::trace_callSetAutoScanInterval(InAutoScanInterval);
	BackendService->Execute_SetAutoScanInterval(BackendService.GetObject(), InAutoScanInterval);
}

void UIviTunerPreferencesLoggingDecorator::OnFavoritesSizeChanged(const FIviTunerGridSize& InFavoritesSize)
{
	IviTunerPreferencesTracer::capture_state(BackendService.GetObject(), this);
	FavoritesSize = InFavoritesSize;
	Execute__GetSignals(this)->OnFavoritesSizeChanged.Broadcast(InFavoritesSize);
}

FIviTunerGridSize UIviTunerPreferencesLoggingDecorator::GetFavoritesSize_Implementation() const
{
	return BackendService->Execute_GetFavoritesSize(BackendService.GetObject());
}

void UIviTunerPreferencesLoggingDecorator::SetFavoritesSize_Implementation(const FIviTunerGridSize& InFavoritesSize)
{
	IviTunerPreferencesTracer::trace_callSetFavoritesSize(InFavoritesSize);
	BackendService->Execute_SetFavoritesSize(BackendService.GetObject(), InFavoritesSize);
}
