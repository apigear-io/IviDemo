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

#include "Implementation/IviTunerTuner.h"
#include "IviTunerTestBase.h"
#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(UIviTunerTunerImplementationPropertyCurrentStationTest, FIviTunerTestBase, "IviTuner.Tuner.Implementation.Property.CurrentStation", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
bool UIviTunerTunerImplementationPropertyCurrentStationTest::RunTest(const FString& Parameters)
{
	// Do implement test here
	TScriptInterface<IIviTunerTunerInterface> test = GetGameInstance()->GetSubsystem<UIviTunerTuner>();
	test->Execute_SetCurrentStation(test.GetObject(), FIviTunerStation());
	TestEqual(TEXT("Getter should return the same value as set by the setter"), test->Execute_GetCurrentStation(test.GetObject()), FIviTunerStation());

	CleanUp();
	return true;
}

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(UIviTunerTunerImplementationPropertyStationsTest, FIviTunerTestBase, "IviTuner.Tuner.Implementation.Property.Stations", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
bool UIviTunerTunerImplementationPropertyStationsTest::RunTest(const FString& Parameters)
{
	// Do implement test here
	TScriptInterface<IIviTunerTunerInterface> test = GetGameInstance()->GetSubsystem<UIviTunerTuner>();
	test->Execute_SetStations(test.GetObject(), TArray<FIviTunerStation>());
	TestEqual(TEXT("Getter should return the same value as set by the setter"), test->Execute_GetStations(test.GetObject()), TArray<FIviTunerStation>());

	CleanUp();
	return true;
}

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(UIviTunerTunerImplementationPropertyAutoScanEnabledTest, FIviTunerTestBase, "IviTuner.Tuner.Implementation.Property.AutoScanEnabled", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
bool UIviTunerTunerImplementationPropertyAutoScanEnabledTest::RunTest(const FString& Parameters)
{
	// Do implement test here
	TScriptInterface<IIviTunerTunerInterface> test = GetGameInstance()->GetSubsystem<UIviTunerTuner>();
	test->Execute_SetAutoScanEnabled(test.GetObject(), false);
	TestEqual(TEXT("Getter should return the same value as set by the setter"), test->Execute_GetAutoScanEnabled(test.GetObject()), false);

	CleanUp();
	return true;
}

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(UIviTunerTunerImplementationPropertyWavebandTest, FIviTunerTestBase, "IviTuner.Tuner.Implementation.Property.Waveband", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
bool UIviTunerTunerImplementationPropertyWavebandTest::RunTest(const FString& Parameters)
{
	// Do implement test here
	TScriptInterface<IIviTunerTunerInterface> test = GetGameInstance()->GetSubsystem<UIviTunerTuner>();
	test->Execute_SetWaveband(test.GetObject(), EIviTunerWaveband::ITW_AM);
	TestEqual(TEXT("Getter should return the same value as set by the setter"), test->Execute_GetWaveband(test.GetObject()), EIviTunerWaveband::ITW_AM);

	CleanUp();
	return true;
}

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(UIviTunerTunerImplementationOperationScanStationsTest, FIviTunerTestBase, "IviTuner.Tuner.Implementation.Operation.ScanStations", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
bool UIviTunerTunerImplementationOperationScanStationsTest::RunTest(const FString& Parameters)
{
	// Do implement test here
	TScriptInterface<IIviTunerTunerInterface> test = GetGameInstance()->GetSubsystem<UIviTunerTuner>();
	test->Execute_ScanStations(test.GetObject());

	CleanUp();
	return true;
}

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(UIviTunerTunerImplementationOperationAutoScanTest, FIviTunerTestBase, "IviTuner.Tuner.Implementation.Operation.AutoScan", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
bool UIviTunerTunerImplementationOperationAutoScanTest::RunTest(const FString& Parameters)
{
	// Do implement test here
	TScriptInterface<IIviTunerTunerInterface> test = GetGameInstance()->GetSubsystem<UIviTunerTuner>();
	test->Execute_AutoScan(test.GetObject());

	CleanUp();
	return true;
}

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(UIviTunerTunerImplementationOperationNextStationTest, FIviTunerTestBase, "IviTuner.Tuner.Implementation.Operation.NextStation", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
bool UIviTunerTunerImplementationOperationNextStationTest::RunTest(const FString& Parameters)
{
	// Do implement test here
	TScriptInterface<IIviTunerTunerInterface> test = GetGameInstance()->GetSubsystem<UIviTunerTuner>();
	test->Execute_NextStation(test.GetObject());

	CleanUp();
	return true;
}

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(UIviTunerTunerImplementationOperationPreviousStationTest, FIviTunerTestBase, "IviTuner.Tuner.Implementation.Operation.PreviousStation", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
bool UIviTunerTunerImplementationOperationPreviousStationTest::RunTest(const FString& Parameters)
{
	// Do implement test here
	TScriptInterface<IIviTunerTunerInterface> test = GetGameInstance()->GetSubsystem<UIviTunerTuner>();
	test->Execute_PreviousStation(test.GetObject());

	CleanUp();
	return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS
