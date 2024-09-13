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

UIviTunerTuner::UIviTunerTuner()
{
	InitData();
}

UIviTunerTuner::~UIviTunerTuner() = default;
FIviTunerStation UIviTunerTuner::GetCurrentStation_Implementation() const
{
	return CurrentStation;
}

void UIviTunerTuner::SetCurrentStation_Implementation(const FIviTunerStation& InCurrentStation)
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

void UIviTunerTuner::SetStations_Implementation(const TArray<FIviTunerStation>& InStations)
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
		if (bAutoScanEnabled)
		{
			GetWorld()->GetTimerManager().SetTimer(AutoScanTimerHandler, this, &UIviTunerTuner::InitData, 1.0f, true);
		}
		else
		{
			GetWorld()->GetTimerManager().ClearTimer(AutoScanTimerHandler);
		}
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

void UIviTunerTuner::ScanStations_Implementation()
{
	InitData();
}

void UIviTunerTuner::AutoScan_Implementation()
{
	Execute_SetAutoScanEnabled(this, !bAutoScanEnabled);
}

void UIviTunerTuner::NextStation_Implementation()
{
	// do nothing if no stations
	if (Stations.Num() == 0)
	{
		return;
	}
	// find index of current station
	const int32 Index = DoFindCurrentStationIndex();
	if (Index < Stations.Num() - 1)
	{
		Execute_SetCurrentStation(this, Stations[Index + 1]);
	}
	else
	{
		Execute_SetCurrentStation(this, Stations[0]);
	}
}



void UIviTunerTuner::PreviousStation_Implementation()
{
	// do nothing if no stations
	if (Stations.Num() == 0)
	{
		return;
	}
	// find index of current station
	const int32 Index = DoFindCurrentStationIndex();
	if (Index > 0)
	{
		Execute_SetCurrentStation(this, Stations[Index - 1]);
	}
	else
	{
		Execute_SetCurrentStation(this, Stations[Stations.Num() - 1]);
	}
}

int32 UIviTunerTuner::DoFindCurrentStationIndex()
{
	for (int32 i = 0; i < Stations.Num(); i++)
	{
		if (Stations[i].id == CurrentStation.id)
		{
			return i;
		}
	}
	return -1;
}

void UIviTunerTuner::InitData()
{
	// add dummy stations
	TArray<FIviTunerStation> LocalStations;
	for (int i = 0; i < 10; i++)
	{
		FIviTunerStation Station = FIviTunerStation();
		Station.id = FString::FromInt(i);
		Station.name = FString::Printf(TEXT("Station %d"), i);
		Station.description = FString::Printf(TEXT("Station %d description"), i);
		Station.frequency = i;
		Station.image = FString::Printf(TEXT("station-%d.png"), i);
		Station.waveband = Waveband;
		LocalStations.Add(Station);
	}
	// shuffle Stations
	LocalStations.Sort([](const FIviTunerStation& a, const FIviTunerStation& b) { return FMath::RandRange(0, 1) == 0; });
	// set current station
	Execute_SetStations(this, LocalStations);
	Execute_SetCurrentStation(this, LocalStations[0]);
}
