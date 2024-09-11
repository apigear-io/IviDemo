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

#include "Engine/LatentActionManager.h"
#include "UObject/Interface.h"
#include "IviTuner_data.h"
#include "IviTunerTunerInterface.generated.h"

/**
 * Declaration for Tuner
 */
// signal delegates
// property delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIviTunerTunerCurrentStationChangedDelegate, const FIviTunerStation&, CurrentStation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIviTunerTunerStationsChangedDelegate, const TArray<FIviTunerStation>&, Stations);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIviTunerTunerAutoScanEnabledChangedDelegate, bool, bAutoScanEnabled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIviTunerTunerWavebandChangedDelegate, EIviTunerWaveband, Waveband);

/**
 * Class UIviTunerTunerInterfaceSignals
 * Contains delegates for properties and signals
 * this is needed since we cannot declare delegates on an UInterface
 */
UCLASS(BlueprintType)
class IVITUNER_API UIviTunerTunerSignals : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "ApiGear|IviTuner|Tuner|Signals", DisplayName = "Property CurrentStation Changed")
	FIviTunerTunerCurrentStationChangedDelegate OnCurrentStationChanged;
	/// C++ wrapper for BP functions to safely call OnCurrentStationChanged.Broadcast
	UFUNCTION(BlueprintCallable, Category = "ApiGear|IviTuner|Tuner|Signals", DisplayName = "Broadcast Property CurrentStation Changed")
	void BroadcastCurrentStationChanged(UPARAM(DisplayName = "CurrentStation") const FIviTunerStation& InCurrentStation)
	{
		OnCurrentStationChanged.Broadcast(InCurrentStation);
	}

	UPROPERTY(BlueprintAssignable, Category = "ApiGear|IviTuner|Tuner|Signals", DisplayName = "Property Stations Changed")
	FIviTunerTunerStationsChangedDelegate OnStationsChanged;
	/// C++ wrapper for BP functions to safely call OnStationsChanged.Broadcast
	UFUNCTION(BlueprintCallable, Category = "ApiGear|IviTuner|Tuner|Signals", DisplayName = "Broadcast Property Stations Changed")
	void BroadcastStationsChanged(UPARAM(DisplayName = "Stations") const TArray<FIviTunerStation>& InStations)
	{
		OnStationsChanged.Broadcast(InStations);
	}

	UPROPERTY(BlueprintAssignable, Category = "ApiGear|IviTuner|Tuner|Signals", DisplayName = "Property AutoScanEnabled Changed")
	FIviTunerTunerAutoScanEnabledChangedDelegate OnAutoScanEnabledChanged;
	/// C++ wrapper for BP functions to safely call OnAutoScanEnabledChanged.Broadcast
	UFUNCTION(BlueprintCallable, Category = "ApiGear|IviTuner|Tuner|Signals", DisplayName = "Broadcast Property AutoScanEnabled Changed")
	void BroadcastAutoScanEnabledChanged(UPARAM(DisplayName = "bAutoScanEnabled") bool bInAutoScanEnabled)
	{
		OnAutoScanEnabledChanged.Broadcast(bInAutoScanEnabled);
	}

	UPROPERTY(BlueprintAssignable, Category = "ApiGear|IviTuner|Tuner|Signals", DisplayName = "Property Waveband Changed")
	FIviTunerTunerWavebandChangedDelegate OnWavebandChanged;
	/// C++ wrapper for BP functions to safely call OnWavebandChanged.Broadcast
	UFUNCTION(BlueprintCallable, Category = "ApiGear|IviTuner|Tuner|Signals", DisplayName = "Broadcast Property Waveband Changed")
	void BroadcastWavebandChanged(UPARAM(DisplayName = "Waveband") EIviTunerWaveband InWaveband)
	{
		OnWavebandChanged.Broadcast(InWaveband);
	}
};

/**
 * Interface UIviTunerTunerInterface only for Unreal Engine's reflection system
 */
UINTERFACE(Blueprintable, MinimalAPI)
class UIviTunerTunerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface IIviTunerTunerInterface
 */
class IVITUNER_API IIviTunerTunerInterface
{
	GENERATED_BODY()

public:
	/// Provides access to the object which holds all the delegates
	/// this is needed since we cannot declare delegates on an UInterface
	/// @return object with signals for property state changes or standalone signals
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ApiGear|IviTuner|Tuner")
	UIviTunerTunerSignals* _GetSignals();
	virtual UIviTunerTunerSignals* _GetSignals_Implementation() = 0;

	// methods
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ApiGear|IviTuner|Tuner|Operations")
	void ScanStations(EIviTunerWaveband Band);
	virtual void ScanStations_Implementation(EIviTunerWaveband Band) = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ApiGear|IviTuner|Tuner|Operations")
	void AutoScan(EIviTunerWaveband Band);
	virtual void AutoScan_Implementation(EIviTunerWaveband Band) = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ApiGear|IviTuner|Tuner|Operations")
	void NextStation();
	virtual void NextStation_Implementation() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ApiGear|IviTuner|Tuner|Operations")
	void PreviousStation();
	virtual void PreviousStation_Implementation() = 0;

	// properties
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ApiGear|IviTuner|Tuner|Properties")
	FIviTunerStation GetCurrentStation() const;
	virtual FIviTunerStation GetCurrentStation_Implementation() const = 0;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ApiGear|IviTuner|Tuner|Properties")
	void SetCurrentStation(const FIviTunerStation& InCurrentStation);
	virtual void SetCurrentStation_Implementation(const FIviTunerStation& InCurrentStation) = 0;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ApiGear|IviTuner|Tuner|Properties")
	TArray<FIviTunerStation> GetStations() const;
	virtual TArray<FIviTunerStation> GetStations_Implementation() const = 0;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ApiGear|IviTuner|Tuner|Properties")
	void SetStations(const TArray<FIviTunerStation>& InStations);
	virtual void SetStations_Implementation(const TArray<FIviTunerStation>& InStations) = 0;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ApiGear|IviTuner|Tuner|Properties")
	bool GetAutoScanEnabled() const;
	virtual bool GetAutoScanEnabled_Implementation() const = 0;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ApiGear|IviTuner|Tuner|Properties")
	void SetAutoScanEnabled(bool bInAutoScanEnabled);
	virtual void SetAutoScanEnabled_Implementation(bool bInAutoScanEnabled) = 0;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ApiGear|IviTuner|Tuner|Properties")
	EIviTunerWaveband GetWaveband() const;
	virtual EIviTunerWaveband GetWaveband_Implementation() const = 0;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ApiGear|IviTuner|Tuner|Properties")
	void SetWaveband(EIviTunerWaveband InWaveband);
	virtual void SetWaveband_Implementation(EIviTunerWaveband InWaveband) = 0;
};
