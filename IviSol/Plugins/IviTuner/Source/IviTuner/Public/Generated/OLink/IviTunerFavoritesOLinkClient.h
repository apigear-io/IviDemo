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

#include "AbstractIviTunerFavorites.h"
THIRD_PARTY_INCLUDES_START
#include "olink/clientnode.h"
THIRD_PARTY_INCLUDES_END
#include "unrealolinksink.h"
#include "ApiGearConnection.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Runtime/Launch/Resources/Version.h"
#if (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION < 27)
#include "Templates/UniquePtr.h"
#else
#include "Templates/PimplPtr.h"
#endif
#include "IviTunerFavoritesOLinkClient.generated.h"

struct IviTunerFavoritesPropertiesData;
DECLARE_LOG_CATEGORY_EXTERN(LogIviTunerFavoritesOLinkClient, Log, All);

UCLASS(NotBlueprintable, BlueprintType)
class IVITUNER_API UIviTunerFavoritesOLinkClient : public UAbstractIviTunerFavorites
{
	GENERATED_BODY()
public:
	explicit UIviTunerFavoritesOLinkClient();

	// only needed in 4.25 to use TUniquePtr<IviTunerFavoritesPropertiesData>
	UIviTunerFavoritesOLinkClient(FVTableHelper& Helper);
	virtual ~UIviTunerFavoritesOLinkClient();

	// subsystem
	void Initialize(FSubsystemCollectionBase& Collection) override;
	void Deinitialize() override;

	// properties
	TArray<FIviTunerStation> GetStations_Implementation() const override;
	void SetStations_Implementation(const TArray<FIviTunerStation>& Stations) override;

	// operations
	void SetStation_Implementation(int32 Index, const FIviTunerStation& Station) override;

	void ResetStation_Implementation(int32 Index) override;

	void ClearAll_Implementation() override;

	UFUNCTION(BlueprintCallable, Category = "ApiGear|IviTuner|Favorites")
	void UseConnection(TScriptInterface<class IApiGearConnection> InConnection);

	/**
	 * Used when the interface client changes subscription status:
	 * either is linked(ready to use) with server side (true) or it is in unlinked state (false).
	 */
	UPROPERTY(BlueprintAssignable, Category = "ApiGear|IviTuner|Favorites|Remote", DisplayName = "Subscription Status Changed")
	FApiGearRemoteApiSubscriptionStatusChangedDelegate _SubscriptionStatusChanged;

	/**
	 * Informs about the subscription state of the interface client.
	 * @return true if the client is subscribed (plugged in the network) and ready to send and receive messages or false if the server cannot be reached.
	 */
	UFUNCTION(BlueprintCallable, Category = "ApiGear|IviTuner|Favorites|Remote")
	bool _IsSubscribed() const;

private:
	void applyState(const nlohmann::json& fields);
	void emitSignal(const std::string& signalName, const nlohmann::json& args);
	std::shared_ptr<FUnrealOLinkSink> m_sink;

	// member variable to store the last sent data
#if (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION < 27)
	TUniquePtr<IviTunerFavoritesPropertiesData> _SentData;
#else
	TPimplPtr<IviTunerFavoritesPropertiesData> _SentData;
#endif
	TScriptInterface<class IApiGearConnection> Connection;
};
