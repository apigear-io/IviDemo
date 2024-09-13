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
#include "IviTunerTunerInterface.h"
#include "AbstractIviTunerTuner.generated.h"

/**
 * Abstract UAbstractIviTunerTuner
 */
UCLASS(Abstract, Blueprintable, NotBlueprintType)
class IVITUNER_API UAbstractIviTunerTuner : public UGameInstanceSubsystem, public IIviTunerTunerInterface
{
	GENERATED_BODY()

public:
	// constructor
	UAbstractIviTunerTuner();
	// subsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// signals
	virtual UIviTunerTunerSignals* _GetSignals_Implementation() override;

	// methods
	virtual void ScanStations_Implementation() override PURE_VIRTUAL(UAbstractIviTunerTuner::ScanStations_Implementation, return;);

	virtual void AutoScan_Implementation() override PURE_VIRTUAL(UAbstractIviTunerTuner::AutoScan_Implementation, return;);

	virtual void NextStation_Implementation() override PURE_VIRTUAL(UAbstractIviTunerTuner::NextStation_Implementation, return;);

	virtual void PreviousStation_Implementation() override PURE_VIRTUAL(UAbstractIviTunerTuner::PreviousStation_Implementation, return;);

	// properties
	virtual FIviTunerStation GetCurrentStation_Implementation() const override PURE_VIRTUAL(UAbstractIviTunerTuner::GetCurrentStation_Implementation, return FIviTunerStation(););
	virtual void SetCurrentStation_Implementation(const FIviTunerStation& InCurrentStation) override PURE_VIRTUAL(UAbstractIviTunerTuner::SetCurrentStation_Implementation, return;);

	virtual TArray<FIviTunerStation> GetStations_Implementation() const override PURE_VIRTUAL(UAbstractIviTunerTuner::GetStations_Implementation, return TArray<FIviTunerStation>(););
	virtual void SetStations_Implementation(const TArray<FIviTunerStation>& InStations) override PURE_VIRTUAL(UAbstractIviTunerTuner::SetStations_Implementation, return;);

	virtual bool GetAutoScanEnabled_Implementation() const override PURE_VIRTUAL(UAbstractIviTunerTuner::GetAutoScanEnabled_Implementation, return false;);
	virtual void SetAutoScanEnabled_Implementation(bool bInAutoScanEnabled) override PURE_VIRTUAL(UAbstractIviTunerTuner::SetAutoScanEnabled_Implementation, return;);

	virtual EIviTunerWaveband GetWaveband_Implementation() const override PURE_VIRTUAL(UAbstractIviTunerTuner::GetWaveband_Implementation, return EIviTunerWaveband::ITW_AM;);
	virtual void SetWaveband_Implementation(EIviTunerWaveband InWaveband) override PURE_VIRTUAL(UAbstractIviTunerTuner::SetWaveband_Implementation, return;);

	virtual bool IsInitialized() const;

protected:
	bool bInitialized = false;

	// properties - local copy
	UPROPERTY(EditAnywhere, BlueprintGetter = GetCurrentStation_Private, BlueprintSetter = SetCurrentStation_Private, Category = "ApiGear|IviTuner|Tuner")
	FIviTunerStation CurrentStation{FIviTunerStation()};

	UFUNCTION(BlueprintGetter, Category = "ApiGear|IviTuner|Tuner|Properties", BlueprintInternalUseOnly)
	FIviTunerStation GetCurrentStation_Private() const;

	UFUNCTION(BlueprintSetter, Category = "ApiGear|IviTuner|Tuner|Properties", BlueprintInternalUseOnly)
	void SetCurrentStation_Private(const FIviTunerStation& InCurrentStation);

	UPROPERTY(EditAnywhere, BlueprintGetter = GetStations_Private, BlueprintSetter = SetStations_Private, Category = "ApiGear|IviTuner|Tuner")
	TArray<FIviTunerStation> Stations{TArray<FIviTunerStation>()};

	UFUNCTION(BlueprintGetter, Category = "ApiGear|IviTuner|Tuner|Properties", BlueprintInternalUseOnly)
	TArray<FIviTunerStation> GetStations_Private() const;

	UFUNCTION(BlueprintSetter, Category = "ApiGear|IviTuner|Tuner|Properties", BlueprintInternalUseOnly)
	void SetStations_Private(const TArray<FIviTunerStation>& InStations);

	UPROPERTY(EditAnywhere, BlueprintGetter = GetAutoScanEnabled_Private, BlueprintSetter = SetAutoScanEnabled_Private, Category = "ApiGear|IviTuner|Tuner")
	bool bAutoScanEnabled{false};

	UFUNCTION(BlueprintGetter, Category = "ApiGear|IviTuner|Tuner|Properties", BlueprintInternalUseOnly)
	bool GetAutoScanEnabled_Private() const;

	UFUNCTION(BlueprintSetter, Category = "ApiGear|IviTuner|Tuner|Properties", BlueprintInternalUseOnly)
	void SetAutoScanEnabled_Private(bool bInAutoScanEnabled);

	UPROPERTY(EditAnywhere, BlueprintGetter = GetWaveband_Private, BlueprintSetter = SetWaveband_Private, Category = "ApiGear|IviTuner|Tuner")
	EIviTunerWaveband Waveband{EIviTunerWaveband::ITW_AM};

	UFUNCTION(BlueprintGetter, Category = "ApiGear|IviTuner|Tuner|Properties", BlueprintInternalUseOnly)
	EIviTunerWaveband GetWaveband_Private() const;

	UFUNCTION(BlueprintSetter, Category = "ApiGear|IviTuner|Tuner|Properties", BlueprintInternalUseOnly)
	void SetWaveband_Private(EIviTunerWaveband InWaveband);

private:
	// signals
	UPROPERTY()
	UIviTunerTunerSignals* IviTunerTunerSignals;
};
