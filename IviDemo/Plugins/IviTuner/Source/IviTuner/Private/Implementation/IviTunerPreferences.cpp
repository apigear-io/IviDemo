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

#include "Implementation/IviTunerPreferences.h"

UIviTunerPreferences::~UIviTunerPreferences() = default;
int32 UIviTunerPreferences::GetAutoScanInterval_Implementation() const
{
	return AutoScanInterval;
}

void UIviTunerPreferences::SetAutoScanInterval_Implementation(int32 InAutoScanInterval)
{
	if (AutoScanInterval != InAutoScanInterval)
	{
		AutoScanInterval = InAutoScanInterval;
		Execute__GetSignals(this)->OnAutoScanIntervalChanged.Broadcast(AutoScanInterval);
	}
}
FIviTunerGridSize UIviTunerPreferences::GetFavoritesSize_Implementation() const
{
	return FavoritesSize;
}

void UIviTunerPreferences::SetFavoritesSize_Implementation(const FIviTunerGridSize& InFavoritesSize)
{
	if (FavoritesSize != InFavoritesSize)
	{
		FavoritesSize = InFavoritesSize;
		Execute__GetSignals(this)->OnFavoritesSizeChanged.Broadcast(FavoritesSize);
	}
}
