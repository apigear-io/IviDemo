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

#include "Implementation/IviTunerFavorites.h"

#include "Generated/IviTunerLogCategories.h"

UIviTunerFavorites::UIviTunerFavorites()
{
	InitData();
}

UIviTunerFavorites::~UIviTunerFavorites() = default;

TArray<FIviTunerStation> UIviTunerFavorites::GetStations_Implementation() const
{
	return Stations;
}

void UIviTunerFavorites::SetStations_Implementation(const TArray<FIviTunerStation>& InStations)
{
	if (Stations != InStations)
	{
		Stations = InStations;
		Execute__GetSignals(this)->OnStationsChanged.Broadcast(Stations);
	}
}

void UIviTunerFavorites::SetStation_Implementation(int32 Index, const FIviTunerStation& Station)
{
	UE_LOG(LogIviTuner, Warning, TEXT("SetStation_Implementation: index %d"), Index);
	// check if index is valid
	if (Index < 0 || Index >= Stations.Num())
	{
		UE_LOG(LogIviTuner, Warning, TEXT("SetStation_Implementation: Station index %d is out of bounds"), Index);
		return;
	}
	// set station
	Stations[Index] = Station;
	Execute__GetSignals(this)->OnStationsChanged.Broadcast(Stations);
}

void UIviTunerFavorites::ResetStation_Implementation(int32 Index)
{
	(void)Index;
	if (Index < 0 || Index >= Stations.Num())
	{
		return;
	}
	Stations[Index] = MakeStation(Index);
	Execute__GetSignals(this)->OnStationsChanged.Broadcast(Stations);
}

void UIviTunerFavorites::ClearAll_Implementation()
{
	InitData();
}


void UIviTunerFavorites::InitData()
{
	// add dummy stations
	TArray<FIviTunerStation> LocalStations;
	for (int i = 0; i < 8; i++)
	{
		LocalStations.Add(MakeStation(i));
	}
	Execute_SetStations(this, LocalStations);
}

FIviTunerStation UIviTunerFavorites::MakeStation(int32 Index)
{
	FIviTunerStation Station = FIviTunerStation();
	Station.id = FString::FromInt(Index);
	Station.name = FString::Printf(TEXT("Station %d"), Index);
	Station.description = FString::Printf(TEXT("Station %d description"), Index);
	Station.frequency = Index;
	Station.image = FString::Printf(TEXT("station-%d.png"), Index);
	Station.waveband = EIviTunerWaveband::ITW_AM;
	return Station;
}