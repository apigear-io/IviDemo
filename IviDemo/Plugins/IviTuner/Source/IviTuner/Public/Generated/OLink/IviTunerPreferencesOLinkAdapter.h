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

#include "IviTunerPreferencesInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UnrealOLinkHost.h"
#include "IviTunerPreferencesOLinkAdapter.generated.h"

/// @brief handles the adaption between the service implementation and the OLink protocol
/// takes an object of the type IIviTunerPreferencesInterface
/// and holds the corresponding IviTunerPreferencesOLinkSource OLink source object
UCLASS(BlueprintType)
class IVITUNER_API UIviTunerPreferencesOLinkAdapter : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	explicit UIviTunerPreferencesOLinkAdapter();
	virtual ~UIviTunerPreferencesOLinkAdapter() = default;

	// subsystem
	void Initialize(FSubsystemCollectionBase& Collection) override;
	void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category = "ApiGear|IviTuner|Preferences")
	void setBackendService(TScriptInterface<IIviTunerPreferencesInterface> InService);

	UFUNCTION(BlueprintCallable, Category = "ApiGear|IviTuner|Preferences")
	void setOLinkHost(TSoftObjectPtr<UUnrealOLinkHost> InHost);

private:
	// signals

	UFUNCTION(Category = "ApiGear|IviTuner|Preferences", BlueprintInternalUseOnly)
	void OnAutoScanIntervalChanged(int32 AutoScanInterval);

	UFUNCTION(Category = "ApiGear|IviTuner|Preferences", BlueprintInternalUseOnly)
	void OnFavoritesSizeChanged(const FIviTunerGridSize& FavoritesSize);

	/** Holds the service backend, can be exchanged with different implementation during runtime */
	UPROPERTY(VisibleAnywhere, Category = "ApiGear|IviTuner|Preferences")
	TScriptInterface<IIviTunerPreferencesInterface> BackendService;

	/** Holds the registry */
	TSharedPtr<ApiGear::ObjectLink::RemoteRegistry> Registry;

	/**
	holds the olink source interface implementation
	must be std::shared_ptr since it is expected by the olink protocol implementation
	*/
	std::shared_ptr<class IviTunerPreferencesOLinkSource> Source;
};
