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
#include "IviTunerGeneralInterface.generated.h"

/**
 * Declaration for General
 */
// signal delegates
// property delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIviTunerGeneralAutoScanIntervalChangedDelegate, int32, AutoScanInterval);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIviTunerGeneralFavoritesSizeChangedDelegate, const FIviTunerGridSize&, FavoritesSize);

/**
 * Class UIviTunerGeneralInterfaceSignals
 * Contains delegates for properties and signals
 * this is needed since we cannot declare delegates on an UInterface
 */
UCLASS(BlueprintType)
class IVITUNER_API UIviTunerGeneralSignals : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "ApiGear|IviTuner|General|Signals", DisplayName = "Property AutoScanInterval Changed")
	FIviTunerGeneralAutoScanIntervalChangedDelegate OnAutoScanIntervalChanged;
	/// C++ wrapper for BP functions to safely call OnAutoScanIntervalChanged.Broadcast
	UFUNCTION(BlueprintCallable, Category = "ApiGear|IviTuner|General|Signals", DisplayName = "Broadcast Property AutoScanInterval Changed")
	void BroadcastAutoScanIntervalChanged(UPARAM(DisplayName = "AutoScanInterval") int32 InAutoScanInterval)
	{
		OnAutoScanIntervalChanged.Broadcast(InAutoScanInterval);
	}

	UPROPERTY(BlueprintAssignable, Category = "ApiGear|IviTuner|General|Signals", DisplayName = "Property FavoritesSize Changed")
	FIviTunerGeneralFavoritesSizeChangedDelegate OnFavoritesSizeChanged;
	/// C++ wrapper for BP functions to safely call OnFavoritesSizeChanged.Broadcast
	UFUNCTION(BlueprintCallable, Category = "ApiGear|IviTuner|General|Signals", DisplayName = "Broadcast Property FavoritesSize Changed")
	void BroadcastFavoritesSizeChanged(UPARAM(DisplayName = "FavoritesSize") const FIviTunerGridSize& InFavoritesSize)
	{
		OnFavoritesSizeChanged.Broadcast(InFavoritesSize);
	}
};

/**
 * Interface UIviTunerGeneralInterface only for Unreal Engine's reflection system
 */
UINTERFACE(Blueprintable, MinimalAPI)
class UIviTunerGeneralInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface IIviTunerGeneralInterface
 */
class IVITUNER_API IIviTunerGeneralInterface
{
	GENERATED_BODY()

public:
	/// Provides access to the object which holds all the delegates
	/// this is needed since we cannot declare delegates on an UInterface
	/// @return object with signals for property state changes or standalone signals
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ApiGear|IviTuner|General")
	UIviTunerGeneralSignals* _GetSignals();
	virtual UIviTunerGeneralSignals* _GetSignals_Implementation() = 0;

	// methods

	// properties
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ApiGear|IviTuner|General|Properties")
	int32 GetAutoScanInterval() const;
	virtual int32 GetAutoScanInterval_Implementation() const = 0;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ApiGear|IviTuner|General|Properties")
	void SetAutoScanInterval(int32 InAutoScanInterval);
	virtual void SetAutoScanInterval_Implementation(int32 InAutoScanInterval) = 0;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ApiGear|IviTuner|General|Properties")
	FIviTunerGridSize GetFavoritesSize() const;
	virtual FIviTunerGridSize GetFavoritesSize_Implementation() const = 0;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ApiGear|IviTuner|General|Properties")
	void SetFavoritesSize(const FIviTunerGridSize& InFavoritesSize);
	virtual void SetFavoritesSize_Implementation(const FIviTunerGridSize& InFavoritesSize) = 0;
};
