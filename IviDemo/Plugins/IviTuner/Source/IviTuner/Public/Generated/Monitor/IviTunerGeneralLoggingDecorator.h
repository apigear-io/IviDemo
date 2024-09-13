
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
#include "AbstractIviTunerGeneral.h"
#include "IviTunerGeneralLoggingDecorator.generated.h"

// General Log
DECLARE_LOG_CATEGORY_EXTERN(LogIviTunerGeneralLoggingDecorator, Log, All);

UCLASS(NotBlueprintable, BlueprintType)
class IVITUNER_API UIviTunerGeneralLoggingDecorator : public UAbstractIviTunerGeneral
{
	GENERATED_BODY()

public:
	explicit UIviTunerGeneralLoggingDecorator();
	virtual ~UIviTunerGeneralLoggingDecorator();

	UFUNCTION(BlueprintCallable, Category = "ApiGear|IviTuner|General")
	void setBackendService(TScriptInterface<IIviTunerGeneralInterface> InService);

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
	UPROPERTY(VisibleAnywhere, Category = "ApiGear|IviTuner|General")
	TScriptInterface<IIviTunerGeneralInterface> BackendService;

	// signals

	UFUNCTION(Category = "ApiGear|IviTuner|General", BlueprintInternalUseOnly)
	void OnAutoScanIntervalChanged(int32 InAutoScanInterval);

	UFUNCTION(Category = "ApiGear|IviTuner|General", BlueprintInternalUseOnly)
	void OnFavoritesSizeChanged(const FIviTunerGridSize& InFavoritesSize);
};
