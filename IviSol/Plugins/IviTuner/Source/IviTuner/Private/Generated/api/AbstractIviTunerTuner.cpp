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
#include "AbstractIviTunerTuner.h"
#include "Async/Async.h"
#include "Engine/Engine.h"
#include "Engine/LatentActionManager.h"
#include "LatentActions.h"

class FIviTunerTunerLatentAction : public FPendingLatentAction
{
private:
	FName ExecutionFunction;
	int32 OutputLink;
	FWeakObjectPtr CallbackTarget;
	bool bInProgress;

public:
	FIviTunerTunerLatentAction(const FLatentActionInfo& LatentInfo)
		: ExecutionFunction(LatentInfo.ExecutionFunction)
		, OutputLink(LatentInfo.Linkage)
		, CallbackTarget(LatentInfo.CallbackTarget)
		, bInProgress(true)
	{
	}

	void Cancel()
	{
		bInProgress = false;
	}

	virtual void UpdateOperation(FLatentResponse& Response) override
	{
		if (bInProgress == false)
		{
			Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
		}
	}

	virtual void NotifyObjectDestroyed()
	{
		Cancel();
	}

	virtual void NotifyActionAborted()
	{
		Cancel();
	}
};

UAbstractIviTunerTuner::UAbstractIviTunerTuner()
{
	IviTunerTunerSignals = NewObject<UIviTunerTunerSignals>();
}

UIviTunerTunerSignals* UAbstractIviTunerTuner::_GetSignals_Implementation()
{
	if (!IviTunerTunerSignals)
	{
		IviTunerTunerSignals = NewObject<UIviTunerTunerSignals>();
	}
	return IviTunerTunerSignals;
}

FIviTunerStation UAbstractIviTunerTuner::GetCurrentStation_Private() const
{
	return Execute_GetCurrentStation(this);
};

void UAbstractIviTunerTuner::SetCurrentStation_Private(const FIviTunerStation& InCurrentStation)
{
	Execute_SetCurrentStation(this, InCurrentStation);
};

TArray<FIviTunerStation> UAbstractIviTunerTuner::GetStations_Private() const
{
	return Execute_GetStations(this);
};

void UAbstractIviTunerTuner::SetStations_Private(const TArray<FIviTunerStation>& InStations)
{
	Execute_SetStations(this, InStations);
};

bool UAbstractIviTunerTuner::GetAutoScanEnabled_Private() const
{
	return Execute_GetAutoScanEnabled(this);
};

void UAbstractIviTunerTuner::SetAutoScanEnabled_Private(bool bInAutoScanEnabled)
{
	Execute_SetAutoScanEnabled(this, bInAutoScanEnabled);
};

EIviTunerWaveband UAbstractIviTunerTuner::GetWaveband_Private() const
{
	return Execute_GetWaveband(this);
};

void UAbstractIviTunerTuner::SetWaveband_Private(EIviTunerWaveband InWaveband)
{
	Execute_SetWaveband(this, InWaveband);
};




void UAbstractIviTunerTuner::Initialize(FSubsystemCollectionBase& Collection)
{
	check(!bInitialized);
	bInitialized = true;

	Super::Initialize(Collection);
}

void UAbstractIviTunerTuner::Deinitialize()
{
	check(bInitialized);
	bInitialized = false;

	if (IviTunerTunerSignals)
	{
		IviTunerTunerSignals->OnCurrentStationChanged.RemoveAll(IviTunerTunerSignals);
		IviTunerTunerSignals->OnStationsChanged.RemoveAll(IviTunerTunerSignals);
		IviTunerTunerSignals->OnAutoScanEnabledChanged.RemoveAll(IviTunerTunerSignals);
		IviTunerTunerSignals->OnWavebandChanged.RemoveAll(IviTunerTunerSignals);
	}

	Super::Deinitialize();
}

bool UAbstractIviTunerTuner::IsInitialized() const
{
	return bInitialized;
}
