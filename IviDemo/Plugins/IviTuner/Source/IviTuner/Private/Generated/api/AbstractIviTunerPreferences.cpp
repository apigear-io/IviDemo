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
#include "AbstractIviTunerPreferences.h"
#include "Async/Async.h"
#include "Engine/Engine.h"
#include "Engine/LatentActionManager.h"
#include "LatentActions.h"

UAbstractIviTunerPreferences::UAbstractIviTunerPreferences()
{
	IviTunerPreferencesSignals = NewObject<UIviTunerPreferencesSignals>();
}

UIviTunerPreferencesSignals* UAbstractIviTunerPreferences::_GetSignals_Implementation()
{
	if (!IviTunerPreferencesSignals)
	{
		IviTunerPreferencesSignals = NewObject<UIviTunerPreferencesSignals>();
	}
	return IviTunerPreferencesSignals;
}

int32 UAbstractIviTunerPreferences::GetAutoScanInterval_Private() const
{
	return Execute_GetAutoScanInterval(this);
};

void UAbstractIviTunerPreferences::SetAutoScanInterval_Private(int32 InAutoScanInterval)
{
	Execute_SetAutoScanInterval(this, InAutoScanInterval);
};

FIviTunerGridSize UAbstractIviTunerPreferences::GetFavoritesSize_Private() const
{
	return Execute_GetFavoritesSize(this);
};

void UAbstractIviTunerPreferences::SetFavoritesSize_Private(const FIviTunerGridSize& InFavoritesSize)
{
	Execute_SetFavoritesSize(this, InFavoritesSize);
};

void UAbstractIviTunerPreferences::Initialize(FSubsystemCollectionBase& Collection)
{
	check(!bInitialized);
	bInitialized = true;

	Super::Initialize(Collection);
}

void UAbstractIviTunerPreferences::Deinitialize()
{
	check(bInitialized);
	bInitialized = false;

	if (IviTunerPreferencesSignals)
	{
		IviTunerPreferencesSignals->OnAutoScanIntervalChanged.RemoveAll(IviTunerPreferencesSignals);
		IviTunerPreferencesSignals->OnFavoritesSizeChanged.RemoveAll(IviTunerPreferencesSignals);
	}

	Super::Deinitialize();
}

bool UAbstractIviTunerPreferences::IsInitialized() const
{
	return bInitialized;
}
