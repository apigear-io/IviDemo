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
#include "AbstractIviTunerFavorites.h"
#include "Async/Async.h"
#include "Engine/Engine.h"
#include "Engine/LatentActionManager.h"
#include "LatentActions.h"

class FIviTunerFavoritesLatentAction : public FPendingLatentAction
{
private:
	FName ExecutionFunction;
	int32 OutputLink;
	FWeakObjectPtr CallbackTarget;
	bool bInProgress;

public:
	FIviTunerFavoritesLatentAction(const FLatentActionInfo& LatentInfo)
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

UAbstractIviTunerFavorites::UAbstractIviTunerFavorites()
{
	IviTunerFavoritesSignals = NewObject<UIviTunerFavoritesSignals>();
}

UIviTunerFavoritesSignals* UAbstractIviTunerFavorites::_GetSignals_Implementation()
{
	if (!IviTunerFavoritesSignals)
	{
		IviTunerFavoritesSignals = NewObject<UIviTunerFavoritesSignals>();
	}
	return IviTunerFavoritesSignals;
}

TArray<FIviTunerStation> UAbstractIviTunerFavorites::GetStations_Private() const
{
	return Execute_GetStations(this);
};

void UAbstractIviTunerFavorites::SetStations_Private(const TArray<FIviTunerStation>& InStations)
{
	Execute_SetStations(this, InStations);
};



void UAbstractIviTunerFavorites::Initialize(FSubsystemCollectionBase& Collection)
{
	check(!bInitialized);
	bInitialized = true;

	Super::Initialize(Collection);
}

void UAbstractIviTunerFavorites::Deinitialize()
{
	check(bInitialized);
	bInitialized = false;

	if (IviTunerFavoritesSignals)
	{
		IviTunerFavoritesSignals->OnStationsChanged.RemoveAll(IviTunerFavoritesSignals);
	}

	Super::Deinitialize();
}

bool UAbstractIviTunerFavorites::IsInitialized() const
{
	return bInitialized;
}
