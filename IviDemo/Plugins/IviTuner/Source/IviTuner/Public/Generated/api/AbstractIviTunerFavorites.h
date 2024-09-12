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

#include "Runtime/Launch/Resources/Version.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "IviTuner_data.h"
#include "IviTunerFavoritesInterface.h"
#include "AbstractIviTunerFavorites.generated.h"

/**
 * Abstract UAbstractIviTunerFavorites
 */
UCLASS(Abstract, Blueprintable, NotBlueprintType)
class IVITUNER_API UAbstractIviTunerFavorites : public UGameInstanceSubsystem, public IIviTunerFavoritesInterface
{
	GENERATED_BODY()

public:
	// constructor
	UAbstractIviTunerFavorites();
	// subsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// signals
	virtual UIviTunerFavoritesSignals* _GetSignals_Implementation() override;

	// methods
	virtual void SetStation_Implementation(int32 Index, const FIviTunerStation& Station) override PURE_VIRTUAL(UAbstractIviTunerFavorites::SetStation_Implementation, return;);

	virtual void ResetStation_Implementation(int32 Index) override PURE_VIRTUAL(UAbstractIviTunerFavorites::ResetStation_Implementation, return;);

	virtual void ClearAll_Implementation() override PURE_VIRTUAL(UAbstractIviTunerFavorites::ClearAll_Implementation, return;);

	// properties
	virtual TArray<FIviTunerStation> GetStations_Implementation() const override PURE_VIRTUAL(UAbstractIviTunerFavorites::GetStations_Implementation, return TArray<FIviTunerStation>(););
	virtual void SetStations_Implementation(const TArray<FIviTunerStation>& InStations) override PURE_VIRTUAL(UAbstractIviTunerFavorites::SetStations_Implementation, return;);

	virtual bool IsInitialized() const;

protected:
	bool bInitialized = false;

	// properties - local copy
	UPROPERTY(EditAnywhere, BlueprintGetter = GetStations_Private, BlueprintSetter = SetStations_Private, Category = "ApiGear|IviTuner|Favorites")
	TArray<FIviTunerStation> Stations{TArray<FIviTunerStation>()};

	UFUNCTION(BlueprintGetter, Category = "ApiGear|IviTuner|Favorites|Properties", BlueprintInternalUseOnly)
	TArray<FIviTunerStation> GetStations_Private() const;

	UFUNCTION(BlueprintSetter, Category = "ApiGear|IviTuner|Favorites|Properties", BlueprintInternalUseOnly)
	void SetStations_Private(const TArray<FIviTunerStation>& InStations);

private:
	// signals
	UPROPERTY()
	UIviTunerFavoritesSignals* IviTunerFavoritesSignals;
};
