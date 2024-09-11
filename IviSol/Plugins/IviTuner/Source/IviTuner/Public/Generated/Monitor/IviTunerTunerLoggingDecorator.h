
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
#include "AbstractIviTunerTuner.h"
#include "IviTunerTunerLoggingDecorator.generated.h"

// General Log
DECLARE_LOG_CATEGORY_EXTERN(LogIviTunerTunerLoggingDecorator, Log, All);

UCLASS(NotBlueprintable, BlueprintType)
class IVITUNER_API UIviTunerTunerLoggingDecorator : public UAbstractIviTunerTuner
{
	GENERATED_BODY()

public:
	explicit UIviTunerTunerLoggingDecorator();
	virtual ~UIviTunerTunerLoggingDecorator();

	UFUNCTION(BlueprintCallable, Category = "ApiGear|IviTuner|Tuner")
	void setBackendService(TScriptInterface<IIviTunerTunerInterface> InService);

	// subsystem
	void Initialize(FSubsystemCollectionBase& Collection) override;
	void Deinitialize() override;

	// properties
	FIviTunerStation GetCurrentStation_Implementation() const override;

	void SetCurrentStation_Implementation(const FIviTunerStation& InCurrentStation) override;

	TArray<FIviTunerStation> GetStations_Implementation() const override;

	void SetStations_Implementation(const TArray<FIviTunerStation>& InStations) override;

	bool GetAutoScanEnabled_Implementation() const override;

	void SetAutoScanEnabled_Implementation(bool bInAutoScanEnabled) override;

	EIviTunerWaveband GetWaveband_Implementation() const override;

	void SetWaveband_Implementation(EIviTunerWaveband InWaveband) override;

	// operations
	void ScanStations_Implementation(EIviTunerWaveband Band) override;

	void AutoScan_Implementation(EIviTunerWaveband Band) override;

	void NextStation_Implementation() override;

	void PreviousStation_Implementation() override;

private:
	/** The connection to the service backend. */
	UPROPERTY(VisibleAnywhere, Category = "ApiGear|IviTuner|Tuner")
	TScriptInterface<IIviTunerTunerInterface> BackendService;

	// signals

	UFUNCTION(Category = "ApiGear|IviTuner|Tuner", BlueprintInternalUseOnly)
	void OnCurrentStationChanged(const FIviTunerStation& InCurrentStation);

	UFUNCTION(Category = "ApiGear|IviTuner|Tuner", BlueprintInternalUseOnly)
	void OnStationsChanged(const TArray<FIviTunerStation>& InStations);

	UFUNCTION(Category = "ApiGear|IviTuner|Tuner", BlueprintInternalUseOnly)
	void OnAutoScanEnabledChanged(bool bInAutoScanEnabled);

	UFUNCTION(Category = "ApiGear|IviTuner|Tuner", BlueprintInternalUseOnly)
	void OnWavebandChanged(EIviTunerWaveband InWaveband);
};
