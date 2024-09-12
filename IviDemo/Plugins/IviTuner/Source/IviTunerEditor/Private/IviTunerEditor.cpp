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

#include "IviTunerEditor.h"
#include "ISettingsModule.h"
#include "PropertyEditorModule.h"
#include "IviTunerSettings.h"
#include "IviTunerConnectionSettings.h"

#define LOCTEXT_NAMESPACE "IviTunerEditor"

void FIviTunerEditorModule::StartupModule()
{
	// register settings
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

	if (SettingsModule != nullptr)
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "ApiGear IviTuner", LOCTEXT("IviTunerSettingsName", "ApiGear IviTuner"), LOCTEXT("IviTunerSettingsDescription", "Project settings for ApiGear IviTuner plugin"), GetMutableDefault<UIviTunerSettings>());
	}

	// register details customization
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));
	PropertyModule.RegisterCustomClassLayout("IviTunerSettings", FOnGetDetailCustomizationInstance::CreateStatic(&FIviTunerConnectionSettingsDetails::MakeInstance));
}

void FIviTunerEditorModule::ShutdownModule()
{
	// unregister settings
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

	if (SettingsModule != nullptr)
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "ApiGear IviTuner");
	}
}

IMPLEMENT_MODULE(FIviTunerEditorModule, IviTunerEditor)

#undef LOCTEXT_NAMESPACE
