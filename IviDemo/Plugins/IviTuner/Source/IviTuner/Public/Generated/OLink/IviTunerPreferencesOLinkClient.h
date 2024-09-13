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

#include "AbstractIviTunerPreferences.h"
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
#include "IviTunerPreferencesOLinkClient.generated.h"

struct IviTunerPreferencesPropertiesData;
DECLARE_LOG_CATEGORY_EXTERN(LogIviTunerPreferencesOLinkClient, Log, All);

UCLASS(NotBlueprintable, BlueprintType)
class IVITUNER_API UIviTunerPreferencesOLinkClient : public UAbstractIviTunerPreferences
{
	GENERATED_BODY()
public:
	explicit UIviTunerPreferencesOLinkClient();

	// only needed in 4.25 to use TUniquePtr<IviTunerPreferencesPropertiesData>
	UIviTunerPreferencesOLinkClient(FVTableHelper& Helper);
	virtual ~UIviTunerPreferencesOLinkClient();

	// subsystem
	void Initialize(FSubsystemCollectionBase& Collection) override;
	void Deinitialize() override;

	// properties
	int32 GetAutoScanInterval_Implementation() const override;
	void SetAutoScanInterval_Implementation(int32 AutoScanInterval) override;

	FIviTunerGridSize GetFavoritesSize_Implementation() const override;
	void SetFavoritesSize_Implementation(const FIviTunerGridSize& FavoritesSize) override;

	// operations

	UFUNCTION(BlueprintCallable, Category = "ApiGear|IviTuner|Preferences")
	void UseConnection(TScriptInterface<class IApiGearConnection> InConnection);

	/**
	 * Used when the interface client changes subscription status:
	 * either is linked(ready to use) with server side (true) or it is in unlinked state (false).
	 */
	UPROPERTY(BlueprintAssignable, Category = "ApiGear|IviTuner|Preferences|Remote", DisplayName = "Subscription Status Changed")
	FApiGearRemoteApiSubscriptionStatusChangedDelegate _SubscriptionStatusChanged;

	/**
	 * Informs about the subscription state of the interface client.
	 * @return true if the client is subscribed (plugged in the network) and ready to send and receive messages or false if the server cannot be reached.
	 */
	UFUNCTION(BlueprintCallable, Category = "ApiGear|IviTuner|Preferences|Remote")
	bool _IsSubscribed() const;

private:
	void applyState(const nlohmann::json& fields);
	void emitSignal(const std::string& signalName, const nlohmann::json& args);
	std::shared_ptr<FUnrealOLinkSink> m_sink;

	// member variable to store the last sent data
#if (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION < 27)
	TUniquePtr<IviTunerPreferencesPropertiesData> _SentData;
#else
	TPimplPtr<IviTunerPreferencesPropertiesData> _SentData;
#endif
	TScriptInterface<class IApiGearConnection> Connection;
};
