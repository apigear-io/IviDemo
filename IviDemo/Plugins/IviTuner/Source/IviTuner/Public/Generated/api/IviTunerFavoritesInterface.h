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
#include "IviTunerFavoritesInterface.generated.h"

/**
 * Declaration for Favorites
 */
// signal delegates
// property delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIviTunerFavoritesStationsChangedDelegate, const TArray<FIviTunerStation>&, Stations);

/**
 * Class UIviTunerFavoritesInterfaceSignals
 * Contains delegates for properties and signals
 * this is needed since we cannot declare delegates on an UInterface
 */
UCLASS(BlueprintType)
class IVITUNER_API UIviTunerFavoritesSignals : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "ApiGear|IviTuner|Favorites|Signals", DisplayName = "Property Stations Changed")
	FIviTunerFavoritesStationsChangedDelegate OnStationsChanged;
	/// C++ wrapper for BP functions to safely call OnStationsChanged.Broadcast
	UFUNCTION(BlueprintCallable, Category = "ApiGear|IviTuner|Favorites|Signals", DisplayName = "Broadcast Property Stations Changed")
	void BroadcastStationsChanged(UPARAM(DisplayName = "Stations") const TArray<FIviTunerStation>& InStations)
	{
		OnStationsChanged.Broadcast(InStations);
	}
};

/**
 * Interface UIviTunerFavoritesInterface only for Unreal Engine's reflection system
 */
UINTERFACE(Blueprintable, MinimalAPI)
class UIviTunerFavoritesInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface IIviTunerFavoritesInterface
 */
class IVITUNER_API IIviTunerFavoritesInterface
{
	GENERATED_BODY()

public:
	/// Provides access to the object which holds all the delegates
	/// this is needed since we cannot declare delegates on an UInterface
	/// @return object with signals for property state changes or standalone signals
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ApiGear|IviTuner|Favorites")
	UIviTunerFavoritesSignals* _GetSignals();
	virtual UIviTunerFavoritesSignals* _GetSignals_Implementation() = 0;

	// methods
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ApiGear|IviTuner|Favorites|Operations")
	void SetStation(int32 Index, const FIviTunerStation& Station);
	virtual void SetStation_Implementation(int32 Index, const FIviTunerStation& Station) = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ApiGear|IviTuner|Favorites|Operations")
	void ResetStation(int32 Index);
	virtual void ResetStation_Implementation(int32 Index) = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ApiGear|IviTuner|Favorites|Operations")
	void ClearAll();
	virtual void ClearAll_Implementation() = 0;

	// properties
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ApiGear|IviTuner|Favorites|Properties")
	TArray<FIviTunerStation> GetStations() const;
	virtual TArray<FIviTunerStation> GetStations_Implementation() const = 0;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ApiGear|IviTuner|Favorites|Properties")
	void SetStations(const TArray<FIviTunerStation>& InStations);
	virtual void SetStations_Implementation(const TArray<FIviTunerStation>& InStations) = 0;
};
