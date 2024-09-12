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

#include "Implementation/IviTunerFavorites.h"
#include "IviTunerTestBase.h"
#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(UIviTunerFavoritesImplementationPropertyStationsTest, FIviTunerTestBase, "IviTuner.Favorites.Implementation.Property.Stations", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
bool UIviTunerFavoritesImplementationPropertyStationsTest::RunTest(const FString& Parameters)
{
	// Do implement test here
	TScriptInterface<IIviTunerFavoritesInterface> test = GetGameInstance()->GetSubsystem<UIviTunerFavorites>();
	test->Execute_SetStations(test.GetObject(), TArray<FIviTunerStation>());
	TestEqual(TEXT("Getter should return the same value as set by the setter"), test->Execute_GetStations(test.GetObject()), TArray<FIviTunerStation>());

	CleanUp();
	return true;
}

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(UIviTunerFavoritesImplementationOperationSetStationTest, FIviTunerTestBase, "IviTuner.Favorites.Implementation.Operation.SetStation", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
bool UIviTunerFavoritesImplementationOperationSetStationTest::RunTest(const FString& Parameters)
{
	// Do implement test here
	TScriptInterface<IIviTunerFavoritesInterface> test = GetGameInstance()->GetSubsystem<UIviTunerFavorites>();
	test->Execute_SetStation(test.GetObject(), 0, FIviTunerStation());

	CleanUp();
	return true;
}

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(UIviTunerFavoritesImplementationOperationResetStationTest, FIviTunerTestBase, "IviTuner.Favorites.Implementation.Operation.ResetStation", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
bool UIviTunerFavoritesImplementationOperationResetStationTest::RunTest(const FString& Parameters)
{
	// Do implement test here
	TScriptInterface<IIviTunerFavoritesInterface> test = GetGameInstance()->GetSubsystem<UIviTunerFavorites>();
	test->Execute_ResetStation(test.GetObject(), 0);

	CleanUp();
	return true;
}

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(UIviTunerFavoritesImplementationOperationClearAllTest, FIviTunerTestBase, "IviTuner.Favorites.Implementation.Operation.ClearAll", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
bool UIviTunerFavoritesImplementationOperationClearAllTest::RunTest(const FString& Parameters)
{
	// Do implement test here
	TScriptInterface<IIviTunerFavoritesInterface> test = GetGameInstance()->GetSubsystem<UIviTunerFavorites>();
	test->Execute_ClearAll(test.GetObject());

	CleanUp();
	return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS
