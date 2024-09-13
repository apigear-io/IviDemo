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
#include "IviTunerGeneralInterface.h"
#include "AbstractIviTunerGeneral.generated.h"

/**
 * Abstract UAbstractIviTunerGeneral
 */
UCLASS(Abstract, Blueprintable, NotBlueprintType)
class IVITUNER_API UAbstractIviTunerGeneral : public UGameInstanceSubsystem, public IIviTunerGeneralInterface
{
	GENERATED_BODY()

public:
	// constructor
	UAbstractIviTunerGeneral();
	// subsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// signals
	virtual UIviTunerGeneralSignals* _GetSignals_Implementation() override;

	// methods

	// properties
	virtual int32 GetAutoScanInterval_Implementation() const override PURE_VIRTUAL(UAbstractIviTunerGeneral::GetAutoScanInterval_Implementation, return 0;);
	virtual void SetAutoScanInterval_Implementation(int32 InAutoScanInterval) override PURE_VIRTUAL(UAbstractIviTunerGeneral::SetAutoScanInterval_Implementation, return;);

	virtual FIviTunerGridSize GetFavoritesSize_Implementation() const override PURE_VIRTUAL(UAbstractIviTunerGeneral::GetFavoritesSize_Implementation, return FIviTunerGridSize(););
	virtual void SetFavoritesSize_Implementation(const FIviTunerGridSize& InFavoritesSize) override PURE_VIRTUAL(UAbstractIviTunerGeneral::SetFavoritesSize_Implementation, return;);

	virtual bool IsInitialized() const;

protected:
	bool bInitialized = false;

	// properties - local copy
	UPROPERTY(EditAnywhere, BlueprintGetter = GetAutoScanInterval_Private, BlueprintSetter = SetAutoScanInterval_Private, Category = "ApiGear|IviTuner|General")
	int32 AutoScanInterval{0};

	UFUNCTION(BlueprintGetter, Category = "ApiGear|IviTuner|General|Properties", BlueprintInternalUseOnly)
	int32 GetAutoScanInterval_Private() const;

	UFUNCTION(BlueprintSetter, Category = "ApiGear|IviTuner|General|Properties", BlueprintInternalUseOnly)
	void SetAutoScanInterval_Private(int32 InAutoScanInterval);

	UPROPERTY(EditAnywhere, BlueprintGetter = GetFavoritesSize_Private, BlueprintSetter = SetFavoritesSize_Private, Category = "ApiGear|IviTuner|General")
	FIviTunerGridSize FavoritesSize{FIviTunerGridSize()};

	UFUNCTION(BlueprintGetter, Category = "ApiGear|IviTuner|General|Properties", BlueprintInternalUseOnly)
	FIviTunerGridSize GetFavoritesSize_Private() const;

	UFUNCTION(BlueprintSetter, Category = "ApiGear|IviTuner|General|Properties", BlueprintInternalUseOnly)
	void SetFavoritesSize_Private(const FIviTunerGridSize& InFavoritesSize);

private:
	// signals
	UPROPERTY()
	UIviTunerGeneralSignals* IviTunerGeneralSignals;
};
