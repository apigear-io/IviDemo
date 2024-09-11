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
	(void)Index;
	(void)Station;
	// do business logic here
}

void UIviTunerFavorites::ResetStation_Implementation(int32 Index)
{
	(void)Index;
	// do business logic here
}

void UIviTunerFavorites::ClearAll_Implementation()
{
	// do business logic here
}
