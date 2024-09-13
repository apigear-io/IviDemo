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

#include "IviTunerFactory.h"
#include "ApiGearSettings.h"
#include "apigearolink.h"
#include "IviTunerSettings.h"
#include "Implementation/IviTunerTuner.h"
#include "Generated/OLink/IviTunerTunerOLinkClient.h"
#include "Implementation/IviTunerFavorites.h"
#include "Generated/OLink/IviTunerFavoritesOLinkClient.h"
#include "Implementation/IviTunerGeneral.h"
#include "Generated/OLink/IviTunerGeneralOLinkClient.h"
#include "IviTunerSettings.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Engine/GameInstance.h"

// General Log
DEFINE_LOG_CATEGORY(LogFIviTunerModuleFactory);

namespace
{
bool IsIviTunerLogEnabled()
{
	UApiGearSettings* settings = GetMutableDefault<UApiGearSettings>();
	return settings->Tracer_EnableDebugLog;
}
} // namespace

#if (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION < 27)
TScriptInterface<IIviTunerTunerInterface> createIviTunerTunerOLink(UGameInstance* GameInstance, FSubsystemCollectionBase& Collection)
{
	if (IsIviTunerLogEnabled())
	{
		UE_LOG(LogFIviTunerModuleFactory, Log, TEXT("createIIviTunerTunerInterface: Using OLink service backend"));
	}

	UIviTunerTunerOLinkClient* Instance = GameInstance->GetSubsystem<UIviTunerTunerOLinkClient>(GameInstance);
	if (!Instance)
	{
		Collection.InitializeDependency(UIviTunerTunerOLinkClient::StaticClass());
		Instance = GameInstance->GetSubsystem<UIviTunerTunerOLinkClient>(GameInstance);
	}

	return Instance;
}

TScriptInterface<IIviTunerTunerInterface> createIviTunerTuner(UGameInstance* GameInstance, FSubsystemCollectionBase& Collection)
{
	if (IsIviTunerLogEnabled())
	{
		UE_LOG(LogFIviTunerModuleFactory, Log, TEXT("createIIviTunerTunerInterface: Using local service backend"));
	}

	UIviTunerTuner* Instance = GameInstance->GetSubsystem<UIviTunerTuner>(GameInstance);
	if (!Instance)
	{
		Collection.InitializeDependency(UIviTunerTuner::StaticClass());
		Instance = GameInstance->GetSubsystem<UIviTunerTuner>(GameInstance);
	}

	return Instance;
}

TScriptInterface<IIviTunerTunerInterface> FIviTunerModuleFactory::createIIviTunerTunerInterface(UGameInstance* GameInstance, FSubsystemCollectionBase& Collection)
{
	UIviTunerSettings* IviTunerSettings = GetMutableDefault<UIviTunerSettings>();

	if (IviTunerSettings->TracerServiceIdentifier == IviTunerLocalBackendIdentifier)
	{
		return createIviTunerTuner(GameInstance, Collection);
	}

	UApiGearSettings* ApiGearSettings = GetMutableDefault<UApiGearSettings>();
	FApiGearConnectionSetting* ConnectionSetting = ApiGearSettings->Connections.Find(IviTunerSettings->TracerServiceIdentifier);

	// Other protocols not supported. To support it edit templates:
	// add protocol handler class for this interface like createIviTunerTunerOLink and other necessary infrastructure
	// extend this function in templates to handle protocol of your choice
	if (ConnectionSetting && ConnectionSetting->ProtocolIdentifier == ApiGearOLinkProtocolIdentifier)
	{
		return createIviTunerTunerOLink(GameInstance, Collection);
	}

	// fallback to local implementation
	return createIviTunerTuner(GameInstance, Collection);
}

#else

TScriptInterface<IIviTunerTunerInterface> createIviTunerTunerOLink(FSubsystemCollectionBase& Collection)
{
	if (IsIviTunerLogEnabled())
	{
		UE_LOG(LogFIviTunerModuleFactory, Log, TEXT("createIIviTunerTunerInterface: Using OLink service backend"));
	}

	UIviTunerTunerOLinkClient* Instance = Cast<UIviTunerTunerOLinkClient>(Collection.InitializeDependency(UIviTunerTunerOLinkClient::StaticClass()));
	return Instance;
}

TScriptInterface<IIviTunerTunerInterface> createIviTunerTuner(FSubsystemCollectionBase& Collection)
{
	if (IsIviTunerLogEnabled())
	{
		UE_LOG(LogFIviTunerModuleFactory, Log, TEXT("createIIviTunerTunerInterface: Using local service backend"));
	}

	UIviTunerTuner* Instance = Cast<UIviTunerTuner>(Collection.InitializeDependency(UIviTunerTuner::StaticClass()));
	return Instance;
}

TScriptInterface<IIviTunerTunerInterface> FIviTunerModuleFactory::createIIviTunerTunerInterface(FSubsystemCollectionBase& Collection)
{
	UIviTunerSettings* IviTunerSettings = GetMutableDefault<UIviTunerSettings>();

	if (IviTunerSettings->TracerServiceIdentifier == IviTunerLocalBackendIdentifier)
	{
		return createIviTunerTuner(Collection);
	}

	UApiGearSettings* ApiGearSettings = GetMutableDefault<UApiGearSettings>();
	FApiGearConnectionSetting* ConnectionSetting = ApiGearSettings->Connections.Find(IviTunerSettings->TracerServiceIdentifier);

	// Other protocols not supported. To support it edit templates:
	// add protocol handler class for this interface like createIviTunerTunerOLink and other necessary infrastructure
	// extend this function in templates to handle protocol of your choice
	if (ConnectionSetting && ConnectionSetting->ProtocolIdentifier == ApiGearOLinkProtocolIdentifier)
	{
		return createIviTunerTunerOLink(Collection);
	}

	// fallback to local implementation
	return createIviTunerTuner(Collection);
}
#endif

#if (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION < 27)
TScriptInterface<IIviTunerFavoritesInterface> createIviTunerFavoritesOLink(UGameInstance* GameInstance, FSubsystemCollectionBase& Collection)
{
	if (IsIviTunerLogEnabled())
	{
		UE_LOG(LogFIviTunerModuleFactory, Log, TEXT("createIIviTunerFavoritesInterface: Using OLink service backend"));
	}

	UIviTunerFavoritesOLinkClient* Instance = GameInstance->GetSubsystem<UIviTunerFavoritesOLinkClient>(GameInstance);
	if (!Instance)
	{
		Collection.InitializeDependency(UIviTunerFavoritesOLinkClient::StaticClass());
		Instance = GameInstance->GetSubsystem<UIviTunerFavoritesOLinkClient>(GameInstance);
	}

	return Instance;
}

TScriptInterface<IIviTunerFavoritesInterface> createIviTunerFavorites(UGameInstance* GameInstance, FSubsystemCollectionBase& Collection)
{
	if (IsIviTunerLogEnabled())
	{
		UE_LOG(LogFIviTunerModuleFactory, Log, TEXT("createIIviTunerFavoritesInterface: Using local service backend"));
	}

	UIviTunerFavorites* Instance = GameInstance->GetSubsystem<UIviTunerFavorites>(GameInstance);
	if (!Instance)
	{
		Collection.InitializeDependency(UIviTunerFavorites::StaticClass());
		Instance = GameInstance->GetSubsystem<UIviTunerFavorites>(GameInstance);
	}

	return Instance;
}

TScriptInterface<IIviTunerFavoritesInterface> FIviTunerModuleFactory::createIIviTunerFavoritesInterface(UGameInstance* GameInstance, FSubsystemCollectionBase& Collection)
{
	UIviTunerSettings* IviTunerSettings = GetMutableDefault<UIviTunerSettings>();

	if (IviTunerSettings->TracerServiceIdentifier == IviTunerLocalBackendIdentifier)
	{
		return createIviTunerFavorites(GameInstance, Collection);
	}

	UApiGearSettings* ApiGearSettings = GetMutableDefault<UApiGearSettings>();
	FApiGearConnectionSetting* ConnectionSetting = ApiGearSettings->Connections.Find(IviTunerSettings->TracerServiceIdentifier);

	// Other protocols not supported. To support it edit templates:
	// add protocol handler class for this interface like createIviTunerFavoritesOLink and other necessary infrastructure
	// extend this function in templates to handle protocol of your choice
	if (ConnectionSetting && ConnectionSetting->ProtocolIdentifier == ApiGearOLinkProtocolIdentifier)
	{
		return createIviTunerFavoritesOLink(GameInstance, Collection);
	}

	// fallback to local implementation
	return createIviTunerFavorites(GameInstance, Collection);
}

#else

TScriptInterface<IIviTunerFavoritesInterface> createIviTunerFavoritesOLink(FSubsystemCollectionBase& Collection)
{
	if (IsIviTunerLogEnabled())
	{
		UE_LOG(LogFIviTunerModuleFactory, Log, TEXT("createIIviTunerFavoritesInterface: Using OLink service backend"));
	}

	UIviTunerFavoritesOLinkClient* Instance = Cast<UIviTunerFavoritesOLinkClient>(Collection.InitializeDependency(UIviTunerFavoritesOLinkClient::StaticClass()));
	return Instance;
}

TScriptInterface<IIviTunerFavoritesInterface> createIviTunerFavorites(FSubsystemCollectionBase& Collection)
{
	if (IsIviTunerLogEnabled())
	{
		UE_LOG(LogFIviTunerModuleFactory, Log, TEXT("createIIviTunerFavoritesInterface: Using local service backend"));
	}

	UIviTunerFavorites* Instance = Cast<UIviTunerFavorites>(Collection.InitializeDependency(UIviTunerFavorites::StaticClass()));
	return Instance;
}

TScriptInterface<IIviTunerFavoritesInterface> FIviTunerModuleFactory::createIIviTunerFavoritesInterface(FSubsystemCollectionBase& Collection)
{
	UIviTunerSettings* IviTunerSettings = GetMutableDefault<UIviTunerSettings>();

	if (IviTunerSettings->TracerServiceIdentifier == IviTunerLocalBackendIdentifier)
	{
		return createIviTunerFavorites(Collection);
	}

	UApiGearSettings* ApiGearSettings = GetMutableDefault<UApiGearSettings>();
	FApiGearConnectionSetting* ConnectionSetting = ApiGearSettings->Connections.Find(IviTunerSettings->TracerServiceIdentifier);

	// Other protocols not supported. To support it edit templates:
	// add protocol handler class for this interface like createIviTunerFavoritesOLink and other necessary infrastructure
	// extend this function in templates to handle protocol of your choice
	if (ConnectionSetting && ConnectionSetting->ProtocolIdentifier == ApiGearOLinkProtocolIdentifier)
	{
		return createIviTunerFavoritesOLink(Collection);
	}

	// fallback to local implementation
	return createIviTunerFavorites(Collection);
}
#endif

#if (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION < 27)
TScriptInterface<IIviTunerGeneralInterface> createIviTunerGeneralOLink(UGameInstance* GameInstance, FSubsystemCollectionBase& Collection)
{
	if (IsIviTunerLogEnabled())
	{
		UE_LOG(LogFIviTunerModuleFactory, Log, TEXT("createIIviTunerGeneralInterface: Using OLink service backend"));
	}

	UIviTunerGeneralOLinkClient* Instance = GameInstance->GetSubsystem<UIviTunerGeneralOLinkClient>(GameInstance);
	if (!Instance)
	{
		Collection.InitializeDependency(UIviTunerGeneralOLinkClient::StaticClass());
		Instance = GameInstance->GetSubsystem<UIviTunerGeneralOLinkClient>(GameInstance);
	}

	return Instance;
}

TScriptInterface<IIviTunerGeneralInterface> createIviTunerGeneral(UGameInstance* GameInstance, FSubsystemCollectionBase& Collection)
{
	if (IsIviTunerLogEnabled())
	{
		UE_LOG(LogFIviTunerModuleFactory, Log, TEXT("createIIviTunerGeneralInterface: Using local service backend"));
	}

	UIviTunerGeneral* Instance = GameInstance->GetSubsystem<UIviTunerGeneral>(GameInstance);
	if (!Instance)
	{
		Collection.InitializeDependency(UIviTunerGeneral::StaticClass());
		Instance = GameInstance->GetSubsystem<UIviTunerGeneral>(GameInstance);
	}

	return Instance;
}

TScriptInterface<IIviTunerGeneralInterface> FIviTunerModuleFactory::createIIviTunerGeneralInterface(UGameInstance* GameInstance, FSubsystemCollectionBase& Collection)
{
	UIviTunerSettings* IviTunerSettings = GetMutableDefault<UIviTunerSettings>();

	if (IviTunerSettings->TracerServiceIdentifier == IviTunerLocalBackendIdentifier)
	{
		return createIviTunerGeneral(GameInstance, Collection);
	}

	UApiGearSettings* ApiGearSettings = GetMutableDefault<UApiGearSettings>();
	FApiGearConnectionSetting* ConnectionSetting = ApiGearSettings->Connections.Find(IviTunerSettings->TracerServiceIdentifier);

	// Other protocols not supported. To support it edit templates:
	// add protocol handler class for this interface like createIviTunerGeneralOLink and other necessary infrastructure
	// extend this function in templates to handle protocol of your choice
	if (ConnectionSetting && ConnectionSetting->ProtocolIdentifier == ApiGearOLinkProtocolIdentifier)
	{
		return createIviTunerGeneralOLink(GameInstance, Collection);
	}

	// fallback to local implementation
	return createIviTunerGeneral(GameInstance, Collection);
}

#else

TScriptInterface<IIviTunerGeneralInterface> createIviTunerGeneralOLink(FSubsystemCollectionBase& Collection)
{
	if (IsIviTunerLogEnabled())
	{
		UE_LOG(LogFIviTunerModuleFactory, Log, TEXT("createIIviTunerGeneralInterface: Using OLink service backend"));
	}

	UIviTunerGeneralOLinkClient* Instance = Cast<UIviTunerGeneralOLinkClient>(Collection.InitializeDependency(UIviTunerGeneralOLinkClient::StaticClass()));
	return Instance;
}

TScriptInterface<IIviTunerGeneralInterface> createIviTunerGeneral(FSubsystemCollectionBase& Collection)
{
	if (IsIviTunerLogEnabled())
	{
		UE_LOG(LogFIviTunerModuleFactory, Log, TEXT("createIIviTunerGeneralInterface: Using local service backend"));
	}

	UIviTunerGeneral* Instance = Cast<UIviTunerGeneral>(Collection.InitializeDependency(UIviTunerGeneral::StaticClass()));
	return Instance;
}

TScriptInterface<IIviTunerGeneralInterface> FIviTunerModuleFactory::createIIviTunerGeneralInterface(FSubsystemCollectionBase& Collection)
{
	UIviTunerSettings* IviTunerSettings = GetMutableDefault<UIviTunerSettings>();

	if (IviTunerSettings->TracerServiceIdentifier == IviTunerLocalBackendIdentifier)
	{
		return createIviTunerGeneral(Collection);
	}

	UApiGearSettings* ApiGearSettings = GetMutableDefault<UApiGearSettings>();
	FApiGearConnectionSetting* ConnectionSetting = ApiGearSettings->Connections.Find(IviTunerSettings->TracerServiceIdentifier);

	// Other protocols not supported. To support it edit templates:
	// add protocol handler class for this interface like createIviTunerGeneralOLink and other necessary infrastructure
	// extend this function in templates to handle protocol of your choice
	if (ConnectionSetting && ConnectionSetting->ProtocolIdentifier == ApiGearOLinkProtocolIdentifier)
	{
		return createIviTunerGeneralOLink(Collection);
	}

	// fallback to local implementation
	return createIviTunerGeneral(Collection);
}
#endif
