
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
#include "Engine/DataTable.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "IviTuner_data.generated.h"

/**
 * Enumeration EIviTunerWaveband
 */
UENUM(BlueprintType)
enum class EIviTunerWaveband : uint8
{
	ITW_AM = 0 UMETA(Displayname = "AM"),
	ITW_FM = 1 UMETA(Displayname = "FM")
};

/**
 * Struct FIviTunerStation
 */
USTRUCT(BlueprintType)
struct IVITUNER_API FIviTunerStation : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ApiGear|IviTuner")
	FString id{FString()};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ApiGear|IviTuner")
	FString name{FString()};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ApiGear|IviTuner")
	FString description{FString()};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ApiGear|IviTuner")
	float frequency{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ApiGear|IviTuner")
	FString image{FString()};

	/**
	 * FIviTunerStation to JSON formatted FString
	 * @param bPrettyPrint Specify whether to use pretty print (e.g., with line endings) or condensed print.
	 * 
	 * @return JSON formatted FString
	 */
	FString ToJSON(bool bPrettyPrint = false) const;

	/** 
	 * FIviTunerStation to FString
	 * WARNING: Do not rely on the format of the string, it may change in the future
	 */
	FString ToString() const;

	/**
	 * FIviTunerStation to FString
	 * WARNING: Do not rely on the format of the string, it may change in the future
	 * 
	 * @return FString 
	 */
	explicit operator FString() const;

	bool operator==(const FIviTunerStation& rhs) const;
	bool operator!=(const FIviTunerStation& rhs) const;
};

/**
 * @brief BP Function library for data types
 */
UCLASS(meta = (BlueprintThreadSafe))
class IVITUNER_API UIviTunerLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/* Convert from uint8 to EIviTunerWaveband @return true if successful */
	UFUNCTION(BlueprintCallable, Category = "ApiGear|IviTuner")
	static bool toIviTunerWaveband(EIviTunerWaveband& ConvertedEnum, uint8 InValue);

	/* Returns true if IviTunerStation A is equal to IviTunerStation B (A == B) */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (IviTunerStation)", CompactNodeTitle = "==", Keywords = "== equal"), Category = "ApiGear|IviTuner")
	static bool EqualEqual_IviTunerStationIviTunerStation(FIviTunerStation A, FIviTunerStation B);

	/* Returns true if IviTunerStation A is not equal to IviTunerStation B (A != B) */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Not Equal (IviTunerStation)", CompactNodeTitle = "!=", Keywords = "!= not equal"), Category = "ApiGear|IviTuner")
	static bool NotEqual_IviTunerStationIviTunerStation(FIviTunerStation A, FIviTunerStation B);

	/** Converts a IviTunerStation to a JSON formatted FString */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To JSON (IviTunerStation)", CompactNodeTitle = "->"), Category = "Utilities|String")
	static FString Conv_IviTunerStationToJSON(const FIviTunerStation& InIviTunerStation);

	/** Converts a IviTunerStation to a string. WARNING: Do not rely on the format of the string, it may change in the future */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To String (IviTunerStation)", CompactNodeTitle = "->", BlueprintAutocast), Category = "Utilities|String")
	static FString Conv_IviTunerStationToString(const FIviTunerStation& InIviTunerStation);
};
