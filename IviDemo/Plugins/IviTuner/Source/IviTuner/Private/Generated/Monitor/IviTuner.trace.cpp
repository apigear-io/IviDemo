#include "IviTuner.trace.h"
#include "Generated/api/IviTuner.json.adapter.h"
#include "tracer.h"

IviTunerTunerTracer::IviTunerTunerTracer()
{
}

void IviTunerTunerTracer::capture_state(UObject* Object, IIviTunerTunerInterface* obj)
{
	nlohmann::json fields_;
	fields_["currentStation"] = obj->Execute_GetCurrentStation(Object);
	fields_["stations"] = obj->Execute_GetStations(Object);
	fields_["autoScanEnabled"] = obj->Execute_GetAutoScanEnabled(Object);
	fields_["waveband"] = obj->Execute_GetWaveband(Object);
	Tracer::instance()->state("ivi.tuner/Tuner", fields_);
}
void IviTunerTunerTracer::trace_callSetCurrentStation(const FIviTunerStation& InCurrentStation)
{
	nlohmann::json fields_;
	fields_["currentStation"] = InCurrentStation;
	Tracer::instance()->call("ivi.tuner/Tuner#_set", fields_);
}
void IviTunerTunerTracer::trace_callSetStations(const TArray<FIviTunerStation>& InStations)
{
	nlohmann::json fields_;
	fields_["stations"] = InStations;
	Tracer::instance()->call("ivi.tuner/Tuner#_set", fields_);
}
void IviTunerTunerTracer::trace_callSetAutoScanEnabled(bool bInAutoScanEnabled)
{
	nlohmann::json fields_;
	fields_["autoScanEnabled"] = bInAutoScanEnabled;
	Tracer::instance()->call("ivi.tuner/Tuner#_set", fields_);
}
void IviTunerTunerTracer::trace_callSetWaveband(EIviTunerWaveband InWaveband)
{
	nlohmann::json fields_;
	fields_["waveband"] = InWaveband;
	Tracer::instance()->call("ivi.tuner/Tuner#_set", fields_);
}

void IviTunerTunerTracer::trace_callScanStations()
{
	nlohmann::json fields_;
	Tracer::instance()->call("ivi.tuner/Tuner#scanStations", fields_);
}

void IviTunerTunerTracer::trace_callAutoScan()
{
	nlohmann::json fields_;
	Tracer::instance()->call("ivi.tuner/Tuner#autoScan", fields_);
}

void IviTunerTunerTracer::trace_callNextStation()
{
	nlohmann::json fields_;
	Tracer::instance()->call("ivi.tuner/Tuner#nextStation", fields_);
}

void IviTunerTunerTracer::trace_callPreviousStation()
{
	nlohmann::json fields_;
	Tracer::instance()->call("ivi.tuner/Tuner#previousStation", fields_);
}

IviTunerFavoritesTracer::IviTunerFavoritesTracer()
{
}

void IviTunerFavoritesTracer::capture_state(UObject* Object, IIviTunerFavoritesInterface* obj)
{
	nlohmann::json fields_;
	fields_["stations"] = obj->Execute_GetStations(Object);
	Tracer::instance()->state("ivi.tuner/Favorites", fields_);
}
void IviTunerFavoritesTracer::trace_callSetStations(const TArray<FIviTunerStation>& InStations)
{
	nlohmann::json fields_;
	fields_["stations"] = InStations;
	Tracer::instance()->call("ivi.tuner/Favorites#_set", fields_);
}

void IviTunerFavoritesTracer::trace_callSetStation(int32 Index, const FIviTunerStation& Station)
{
	nlohmann::json fields_;
	fields_["index"] = Index;
	fields_["station"] = Station;
	Tracer::instance()->call("ivi.tuner/Favorites#setStation", fields_);
}

void IviTunerFavoritesTracer::trace_callResetStation(int32 Index)
{
	nlohmann::json fields_;
	fields_["index"] = Index;
	Tracer::instance()->call("ivi.tuner/Favorites#resetStation", fields_);
}

void IviTunerFavoritesTracer::trace_callClearAll()
{
	nlohmann::json fields_;
	Tracer::instance()->call("ivi.tuner/Favorites#clearAll", fields_);
}

IviTunerGeneralTracer::IviTunerGeneralTracer()
{
}

void IviTunerGeneralTracer::capture_state(UObject* Object, IIviTunerGeneralInterface* obj)
{
	nlohmann::json fields_;
	fields_["autoScanInterval"] = obj->Execute_GetAutoScanInterval(Object);
	fields_["favoritesSize"] = obj->Execute_GetFavoritesSize(Object);
	Tracer::instance()->state("ivi.tuner/General", fields_);
}
void IviTunerGeneralTracer::trace_callSetAutoScanInterval(int32 InAutoScanInterval)
{
	nlohmann::json fields_;
	fields_["autoScanInterval"] = InAutoScanInterval;
	Tracer::instance()->call("ivi.tuner/General#_set", fields_);
}
void IviTunerGeneralTracer::trace_callSetFavoritesSize(const FIviTunerGridSize& InFavoritesSize)
{
	nlohmann::json fields_;
	fields_["favoritesSize"] = InFavoritesSize;
	Tracer::instance()->call("ivi.tuner/General#_set", fields_);
}
