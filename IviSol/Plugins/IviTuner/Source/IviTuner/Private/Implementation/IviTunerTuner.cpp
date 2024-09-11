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

#include "Implementation/IviTunerTuner.h"

#include "Generated/IviTunerLogCategories.h"

UIviTunerTuner::~UIviTunerTuner() = default;
FIviTunerStation UIviTunerTuner::GetCurrentStation_Implementation() const
{
	return CurrentStation;
}

void UIviTunerTuner::SetCurrentStation_Implementation(const FIviTunerStation &InCurrentStation)
{
	if (CurrentStation != InCurrentStation)
	{
		CurrentStation = InCurrentStation;
		Execute__GetSignals(this)->OnCurrentStationChanged.Broadcast(CurrentStation);
	}
}
TArray<FIviTunerStation> UIviTunerTuner::GetStations_Implementation() const
{
	return Stations;
}

void UIviTunerTuner::SetStations_Implementation(const TArray<FIviTunerStation> &InStations)
{
	if (Stations != InStations)
	{
		Stations = InStations;
		Execute__GetSignals(this)->OnStationsChanged.Broadcast(Stations);
	}
}
bool UIviTunerTuner::GetAutoScanEnabled_Implementation() const
{
	return bAutoScanEnabled;
}

void UIviTunerTuner::SetAutoScanEnabled_Implementation(bool bInAutoScanEnabled)
{
	if (bAutoScanEnabled != bInAutoScanEnabled)
	{
		bAutoScanEnabled = bInAutoScanEnabled;
		Execute__GetSignals(this)->OnAutoScanEnabledChanged.Broadcast(bAutoScanEnabled);
	}
}
EIviTunerWaveband UIviTunerTuner::GetWaveband_Implementation() const
{
	return Waveband;
}

void UIviTunerTuner::SetWaveband_Implementation(EIviTunerWaveband InWaveband)
{
	if (Waveband != InWaveband)
	{
		Waveband = InWaveband;
		Execute__GetSignals(this)->OnWavebandChanged.Broadcast(Waveband);
	}
}

void UIviTunerTuner::ScanStations_Implementation(EIviTunerWaveband Band)
{
	(void)Band;
	// do business logic here
	UE_LOG(LogIviTuner, Warning, TEXT("CPP Scan Station Called"))
}

void UIviTunerTuner::AutoScan_Implementation(EIviTunerWaveband Band)
{
	(void)Band;
	// do business logic here
}

void UIviTunerTuner::NextStation_Implementation()
{
	// do business logic here
}

void UIviTunerTuner::PreviousStation_Implementation()
{
	// do business logic here
}
