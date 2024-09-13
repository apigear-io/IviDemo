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

#include "Implementation/IviTunerPreferences.h"
#include "IviTunerTestBase.h"
#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(UIviTunerPreferencesImplementationPropertyAutoScanIntervalTest, FIviTunerTestBase, "IviTuner.Preferences.Implementation.Property.AutoScanInterval", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
bool UIviTunerPreferencesImplementationPropertyAutoScanIntervalTest::RunTest(const FString& Parameters)
{
	// Do implement test here
	TScriptInterface<IIviTunerPreferencesInterface> test = GetGameInstance()->GetSubsystem<UIviTunerPreferences>();
	test->Execute_SetAutoScanInterval(test.GetObject(), 0);
	TestEqual(TEXT("Getter should return the same value as set by the setter"), test->Execute_GetAutoScanInterval(test.GetObject()), 0);

	CleanUp();
	return true;
}

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(UIviTunerPreferencesImplementationPropertyFavoritesSizeTest, FIviTunerTestBase, "IviTuner.Preferences.Implementation.Property.FavoritesSize", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
bool UIviTunerPreferencesImplementationPropertyFavoritesSizeTest::RunTest(const FString& Parameters)
{
	// Do implement test here
	TScriptInterface<IIviTunerPreferencesInterface> test = GetGameInstance()->GetSubsystem<UIviTunerPreferences>();
	test->Execute_SetFavoritesSize(test.GetObject(), FIviTunerGridSize());
	TestEqual(TEXT("Getter should return the same value as set by the setter"), test->Execute_GetFavoritesSize(test.GetObject()), FIviTunerGridSize());

	CleanUp();
	return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS
