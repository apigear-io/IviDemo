
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
#include "Generated/api/AbstractIviTunerTuner.h"
#include "IviTunerTuner.generated.h"

UCLASS(BlueprintType)
class IVITUNER_API UIviTunerTuner : public UAbstractIviTunerTuner
{
	GENERATED_BODY()
public:

	UIviTunerTuner();
	virtual ~UIviTunerTuner();

	// properties
	FIviTunerStation GetCurrentStation_Implementation() const override;
	void SetCurrentStation_Implementation(const FIviTunerStation& CurrentStation) override;

	TArray<FIviTunerStation> GetStations_Implementation() const override;
	void SetStations_Implementation(const TArray<FIviTunerStation>& Stations) override;

	bool GetAutoScanEnabled_Implementation() const override;
	void SetAutoScanEnabled_Implementation(bool bAutoScanEnabled) override;

	EIviTunerWaveband GetWaveband_Implementation() const override;
	void SetWaveband_Implementation(EIviTunerWaveband Waveband) override;

	// operations
	void ScanStations_Implementation() override;

	void AutoScan_Implementation() override;

	void NextStation_Implementation() override;

	void PreviousStation_Implementation() override;
private:
	void InitData();
	int32 DoFindCurrentStationIndex();
	FTimerHandle AutoScanTimerHandler;
};
