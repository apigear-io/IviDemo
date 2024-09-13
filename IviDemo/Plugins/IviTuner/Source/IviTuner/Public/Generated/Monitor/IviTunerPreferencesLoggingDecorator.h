
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
#include "AbstractIviTunerPreferences.h"
#include "IviTunerPreferencesLoggingDecorator.generated.h"

// General Log
DECLARE_LOG_CATEGORY_EXTERN(LogIviTunerPreferencesLoggingDecorator, Log, All);

UCLASS(NotBlueprintable, BlueprintType)
class IVITUNER_API UIviTunerPreferencesLoggingDecorator : public UAbstractIviTunerPreferences
{
	GENERATED_BODY()

public:
	explicit UIviTunerPreferencesLoggingDecorator();
	virtual ~UIviTunerPreferencesLoggingDecorator();

	UFUNCTION(BlueprintCallable, Category = "ApiGear|IviTuner|Preferences")
	void setBackendService(TScriptInterface<IIviTunerPreferencesInterface> InService);

	// subsystem
	void Initialize(FSubsystemCollectionBase& Collection) override;
	void Deinitialize() override;

	// properties
	int32 GetAutoScanInterval_Implementation() const override;

	void SetAutoScanInterval_Implementation(int32 InAutoScanInterval) override;

	FIviTunerGridSize GetFavoritesSize_Implementation() const override;

	void SetFavoritesSize_Implementation(const FIviTunerGridSize& InFavoritesSize) override;

	// operations
private:
	/** The connection to the service backend. */
	UPROPERTY(VisibleAnywhere, Category = "ApiGear|IviTuner|Preferences")
	TScriptInterface<IIviTunerPreferencesInterface> BackendService;

	// signals

	UFUNCTION(Category = "ApiGear|IviTuner|Preferences", BlueprintInternalUseOnly)
	void OnAutoScanIntervalChanged(int32 InAutoScanInterval);

	UFUNCTION(Category = "ApiGear|IviTuner|Preferences", BlueprintInternalUseOnly)
	void OnFavoritesSizeChanged(const FIviTunerGridSize& InFavoritesSize);
};
