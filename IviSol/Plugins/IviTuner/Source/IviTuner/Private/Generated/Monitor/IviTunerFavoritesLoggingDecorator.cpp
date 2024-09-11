
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
#include "Generated/Monitor/IviTunerFavoritesLoggingDecorator.h"
#include "IviTuner.trace.h"
#include "IviTunerFactory.h"
#include "Runtime/Launch/Resources/Version.h"

DEFINE_LOG_CATEGORY(LogIviTunerFavoritesLoggingDecorator);
UIviTunerFavoritesLoggingDecorator::UIviTunerFavoritesLoggingDecorator()
	: UAbstractIviTunerFavorites()
{
}

UIviTunerFavoritesLoggingDecorator::~UIviTunerFavoritesLoggingDecorator() = default;

void UIviTunerFavoritesLoggingDecorator::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
#if (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION < 27)
	setBackendService(FIviTunerModuleFactory::createIIviTunerFavoritesInterface(GetGameInstance(), Collection));
#else
	setBackendService(FIviTunerModuleFactory::createIIviTunerFavoritesInterface(Collection));
#endif
}

void UIviTunerFavoritesLoggingDecorator::Deinitialize()
{
	Super::Deinitialize();
	BackendService = nullptr;
}

void UIviTunerFavoritesLoggingDecorator::setBackendService(TScriptInterface<IIviTunerFavoritesInterface> InService)
{
	// unsubscribe from old backend
	if (BackendService != nullptr)
	{
		UIviTunerFavoritesSignals* BackendSignals = BackendService->Execute__GetSignals(BackendService.GetObject());
		checkf(BackendSignals, TEXT("Cannot unsubscribe from delegates from backend service IviTunerFavorites"));
		BackendSignals->OnStationsChanged.RemoveDynamic(this, &UIviTunerFavoritesLoggingDecorator::OnStationsChanged);
	}

	// only set if interface is implemented
	checkf(InService.GetInterface() != nullptr, TEXT("Cannot set backend service - interface IviTunerFavorites is not fully implemented"));

	// subscribe to new backend
	BackendService = InService;
	UIviTunerFavoritesSignals* BackendSignals = BackendService->Execute__GetSignals(BackendService.GetObject());
	checkf(BackendSignals, TEXT("Cannot unsubscribe from delegates from backend service IviTunerFavorites"));
	// connect property changed signals or simple events
	BackendSignals->OnStationsChanged.AddDynamic(this, &UIviTunerFavoritesLoggingDecorator::OnStationsChanged);
	// populate service state to proxy
	Stations = BackendService->Execute_GetStations(BackendService.GetObject());
}

void UIviTunerFavoritesLoggingDecorator::OnStationsChanged(const TArray<FIviTunerStation>& InStations)
{
	IviTunerFavoritesTracer::capture_state(BackendService.GetObject(), this);
	Stations = InStations;
	Execute__GetSignals(this)->OnStationsChanged.Broadcast(InStations);
}

TArray<FIviTunerStation> UIviTunerFavoritesLoggingDecorator::GetStations_Implementation() const
{
	return BackendService->Execute_GetStations(BackendService.GetObject());
}

void UIviTunerFavoritesLoggingDecorator::SetStations_Implementation(const TArray<FIviTunerStation>& InStations)
{
	IviTunerFavoritesTracer::trace_callSetStations(InStations);
	BackendService->Execute_SetStations(BackendService.GetObject(), InStations);
}

void UIviTunerFavoritesLoggingDecorator::SetStation_Implementation(int32 Index, const FIviTunerStation& Station)
{
	IviTunerFavoritesTracer::trace_callSetStation(Index, Station);
	BackendService->Execute_SetStation(BackendService.GetObject(), Index, Station);
}

void UIviTunerFavoritesLoggingDecorator::ResetStation_Implementation(int32 Index)
{
	IviTunerFavoritesTracer::trace_callResetStation(Index);
	BackendService->Execute_ResetStation(BackendService.GetObject(), Index);
}

void UIviTunerFavoritesLoggingDecorator::ClearAll_Implementation()
{
	IviTunerFavoritesTracer::trace_callClearAll();
	BackendService->Execute_ClearAll(BackendService.GetObject());
}
