
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

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AbstractIviTunerFavorites.h"
#include "IviTunerFavoritesLoggingDecorator.generated.h"

// General Log
DECLARE_LOG_CATEGORY_EXTERN(LogIviTunerFavoritesLoggingDecorator, Log, All);

UCLASS(NotBlueprintable, BlueprintType)
class IVITUNER_API UIviTunerFavoritesLoggingDecorator : public UAbstractIviTunerFavorites
{
	GENERATED_BODY()

public:
	explicit UIviTunerFavoritesLoggingDecorator();
	virtual ~UIviTunerFavoritesLoggingDecorator();

	UFUNCTION(BlueprintCallable, Category = "ApiGear|IviTuner|Favorites")
	void setBackendService(TScriptInterface<IIviTunerFavoritesInterface> InService);

	// subsystem
	void Initialize(FSubsystemCollectionBase& Collection) override;
	void Deinitialize() override;

	// properties
	TArray<FIviTunerStation> GetStations_Implementation() const override;

	void SetStations_Implementation(const TArray<FIviTunerStation>& InStations) override;

	// operations
	void SetStation_Implementation(int32 Index, const FIviTunerStation& Station) override;

	void ResetStation_Implementation(int32 Index) override;

	void ClearAll_Implementation() override;

private:
	/** The connection to the service backend. */
	UPROPERTY(VisibleAnywhere, Category = "ApiGear|IviTuner|Favorites")
	TScriptInterface<IIviTunerFavoritesInterface> BackendService;

	// signals

	UFUNCTION(Category = "ApiGear|IviTuner|Favorites", BlueprintInternalUseOnly)
	void OnStationsChanged(const TArray<FIviTunerStation>& InStations);
};
