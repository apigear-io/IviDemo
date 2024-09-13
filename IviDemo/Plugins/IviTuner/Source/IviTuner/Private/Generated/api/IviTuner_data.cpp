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

#include "IviTuner_data.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"

/**
 * Enumeration EIviTunerWaveband
 */
bool UIviTunerLibrary::toIviTunerWaveband(EIviTunerWaveband& ConvertedEnum, uint8 InValue)
{
	bool bSuccessful = false;
	switch (InValue)
	{
	case 0:
		ConvertedEnum = EIviTunerWaveband::ITW_AM;
		bSuccessful = true;
		break;
	case 1:
		ConvertedEnum = EIviTunerWaveband::ITW_FM;
		bSuccessful = true;
		break;
	default:
		ConvertedEnum = EIviTunerWaveband::ITW_AM;
	}
	return bSuccessful;
}

bool FIviTunerStation::operator==(const FIviTunerStation& rhs) const
{
	return (id == rhs.id) && (name == rhs.name) && (description == rhs.description) && (frequency == rhs.frequency) && (image == rhs.image) && (waveband == rhs.waveband);
}

bool FIviTunerStation::operator!=(const FIviTunerStation& rhs) const
{
	return !operator==(rhs);
}

FIviTunerStation::operator FString() const
{
	return ToString();
}

FString FIviTunerStation::ToString() const
{
	return ToJSON(true);
}

FString FIviTunerStation::ToJSON(bool bPrettyPrint) const
{
	FString JSONString;
	FJsonObjectConverter::UStructToJsonObjectString(*this, JSONString, 0, 0, 0, nullptr, bPrettyPrint);
	return JSONString;
}

bool FIviTunerGridSize::operator==(const FIviTunerGridSize& rhs) const
{
	return (rows == rhs.rows) && (columns == rhs.columns);
}

bool FIviTunerGridSize::operator!=(const FIviTunerGridSize& rhs) const
{
	return !operator==(rhs);
}

FIviTunerGridSize::operator FString() const
{
	return ToString();
}

FString FIviTunerGridSize::ToString() const
{
	return ToJSON(true);
}

FString FIviTunerGridSize::ToJSON(bool bPrettyPrint) const
{
	FString JSONString;
	FJsonObjectConverter::UStructToJsonObjectString(*this, JSONString, 0, 0, 0, nullptr, bPrettyPrint);
	return JSONString;
}

/* Returns true if IviTunerStation A is equal to IviTunerStation B (A == B) */
bool UIviTunerLibrary::EqualEqual_IviTunerStationIviTunerStation(FIviTunerStation A, FIviTunerStation B)
{
	return A == B;
}

/* Returns true if IviTunerStation A is not equal to IviTunerStation B (A != B) */
bool UIviTunerLibrary::NotEqual_IviTunerStationIviTunerStation(FIviTunerStation A, FIviTunerStation B)
{
	return A != B;
}

FString UIviTunerLibrary::Conv_IviTunerStationToString(const FIviTunerStation& InIviTunerStation)
{
	return InIviTunerStation.ToString();
}

FString UIviTunerLibrary::Conv_IviTunerStationToJSON(const FIviTunerStation& InIviTunerStation)
{
	return InIviTunerStation.ToJSON();
}

/* Returns true if IviTunerGridSize A is equal to IviTunerGridSize B (A == B) */
bool UIviTunerLibrary::EqualEqual_IviTunerGridSizeIviTunerGridSize(FIviTunerGridSize A, FIviTunerGridSize B)
{
	return A == B;
}

/* Returns true if IviTunerGridSize A is not equal to IviTunerGridSize B (A != B) */
bool UIviTunerLibrary::NotEqual_IviTunerGridSizeIviTunerGridSize(FIviTunerGridSize A, FIviTunerGridSize B)
{
	return A != B;
}

FString UIviTunerLibrary::Conv_IviTunerGridSizeToString(const FIviTunerGridSize& InIviTunerGridSize)
{
	return InIviTunerGridSize.ToString();
}

FString UIviTunerLibrary::Conv_IviTunerGridSizeToJSON(const FIviTunerGridSize& InIviTunerGridSize)
{
	return InIviTunerGridSize.ToJSON();
}
