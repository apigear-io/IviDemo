
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
#include "Generated/api/AbstractIviTunerFavorites.h"
#include "IviTunerFavorites.generated.h"

UCLASS(BlueprintType)
class IVITUNER_API UIviTunerFavorites : public UAbstractIviTunerFavorites
{
	GENERATED_BODY()
public:
	UIviTunerFavorites();
	virtual ~UIviTunerFavorites();

	// properties
	TArray<FIviTunerStation> GetStations_Implementation() const override;
	void SetStations_Implementation(const TArray<FIviTunerStation>& Stations) override;

	// operations
	void SetStation_Implementation(int32 Index, const FIviTunerStation& Station) override;

	void ResetStation_Implementation(int32 Index) override;

	void ClearAll_Implementation() override;
private:
	void InitData();
	static FIviTunerStation MakeStation(int32 Index);
};
