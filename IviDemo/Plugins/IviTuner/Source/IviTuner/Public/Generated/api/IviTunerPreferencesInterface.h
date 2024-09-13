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
#pragma once

#include "Engine/LatentActionManager.h"
#include "UObject/Interface.h"
#include "IviTuner_data.h"
#include "IviTunerPreferencesInterface.generated.h"

/**
 * Declaration for Preferences
 */
// signal delegates
// property delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIviTunerPreferencesAutoScanIntervalChangedDelegate, int32, AutoScanInterval);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIviTunerPreferencesFavoritesSizeChangedDelegate, const FIviTunerGridSize&, FavoritesSize);

/**
 * Class UIviTunerPreferencesInterfaceSignals
 * Contains delegates for properties and signals
 * this is needed since we cannot declare delegates on an UInterface
 */
UCLASS(BlueprintType)
class IVITUNER_API UIviTunerPreferencesSignals : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "ApiGear|IviTuner|Preferences|Signals", DisplayName = "Property AutoScanInterval Changed")
	FIviTunerPreferencesAutoScanIntervalChangedDelegate OnAutoScanIntervalChanged;
	/// C++ wrapper for BP functions to safely call OnAutoScanIntervalChanged.Broadcast
	UFUNCTION(BlueprintCallable, Category = "ApiGear|IviTuner|Preferences|Signals", DisplayName = "Broadcast Property AutoScanInterval Changed")
	void BroadcastAutoScanIntervalChanged(UPARAM(DisplayName = "AutoScanInterval") int32 InAutoScanInterval)
	{
		OnAutoScanIntervalChanged.Broadcast(InAutoScanInterval);
	}

	UPROPERTY(BlueprintAssignable, Category = "ApiGear|IviTuner|Preferences|Signals", DisplayName = "Property FavoritesSize Changed")
	FIviTunerPreferencesFavoritesSizeChangedDelegate OnFavoritesSizeChanged;
	/// C++ wrapper for BP functions to safely call OnFavoritesSizeChanged.Broadcast
	UFUNCTION(BlueprintCallable, Category = "ApiGear|IviTuner|Preferences|Signals", DisplayName = "Broadcast Property FavoritesSize Changed")
	void BroadcastFavoritesSizeChanged(UPARAM(DisplayName = "FavoritesSize") const FIviTunerGridSize& InFavoritesSize)
	{
		OnFavoritesSizeChanged.Broadcast(InFavoritesSize);
	}
};

/**
 * Interface UIviTunerPreferencesInterface only for Unreal Engine's reflection system
 */
UINTERFACE(Blueprintable, MinimalAPI)
class UIviTunerPreferencesInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface IIviTunerPreferencesInterface
 */
class IVITUNER_API IIviTunerPreferencesInterface
{
	GENERATED_BODY()

public:
	/// Provides access to the object which holds all the delegates
	/// this is needed since we cannot declare delegates on an UInterface
	/// @return object with signals for property state changes or standalone signals
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ApiGear|IviTuner|Preferences")
	UIviTunerPreferencesSignals* _GetSignals();
	virtual UIviTunerPreferencesSignals* _GetSignals_Implementation() = 0;

	// methods

	// properties
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ApiGear|IviTuner|Preferences|Properties")
	int32 GetAutoScanInterval() const;
	virtual int32 GetAutoScanInterval_Implementation() const = 0;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ApiGear|IviTuner|Preferences|Properties")
	void SetAutoScanInterval(int32 InAutoScanInterval);
	virtual void SetAutoScanInterval_Implementation(int32 InAutoScanInterval) = 0;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ApiGear|IviTuner|Preferences|Properties")
	FIviTunerGridSize GetFavoritesSize() const;
	virtual FIviTunerGridSize GetFavoritesSize_Implementation() const = 0;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ApiGear|IviTuner|Preferences|Properties")
	void SetFavoritesSize(const FIviTunerGridSize& InFavoritesSize);
	virtual void SetFavoritesSize_Implementation(const FIviTunerGridSize& InFavoritesSize) = 0;
};
