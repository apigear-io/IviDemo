#pragma once

#include "IviTuner_apig.h"

class IviTunerTunerTracer
{
public:
	IviTunerTunerTracer();
	static void capture_state(UObject* Object, IIviTunerTunerInterface* obj);
	static void trace_callSetCurrentStation(const FIviTunerStation& InCurrentStation);
	static void trace_callSetStations(const TArray<FIviTunerStation>& InStations);
	static void trace_callSetAutoScanEnabled(bool bInAutoScanEnabled);
	static void trace_callSetWaveband(EIviTunerWaveband InWaveband);
	static void trace_callScanStations();
	static void trace_callAutoScan();
	static void trace_callNextStation();
	static void trace_callPreviousStation();
};

class IviTunerFavoritesTracer
{
public:
	IviTunerFavoritesTracer();
	static void capture_state(UObject* Object, IIviTunerFavoritesInterface* obj);
	static void trace_callSetStations(const TArray<FIviTunerStation>& InStations);
	static void trace_callSetStation(int32 Index, const FIviTunerStation& Station);
	static void trace_callResetStation(int32 Index);
	static void trace_callClearAll();
};

class IviTunerGeneralTracer
{
public:
	IviTunerGeneralTracer();
	static void capture_state(UObject* Object, IIviTunerGeneralInterface* obj);
	static void trace_callSetAutoScanInterval(int32 InAutoScanInterval);
	static void trace_callSetFavoritesSize(const FIviTunerGridSize& InFavoritesSize);
};
