#pragma once

#include "apigear.json.adapter.h"

static void from_json(const nlohmann::json& j, FIviTunerStation& p)
{
	p.id = j.at("id").get<FString>();
	p.name = j.at("name").get<FString>();
	p.description = j.at("description").get<FString>();
	p.frequency = j.at("frequency").get<float>();
	p.image = j.at("image").get<FString>();
	p.waveband = j.at("waveband").get<EIviTunerWaveband>();
}

static void to_json(nlohmann::json& j, const FIviTunerStation& p)
{
	j = nlohmann::json{{"id", p.id}, {"name", p.name}, {"description", p.description}, {"frequency", p.frequency}, {"image", p.image}, {"waveband", p.waveband}};
}

static void from_json(const nlohmann::json& j, FIviTunerGridSize& p)
{
	p.rows = j.at("rows").get<int32>();
	p.columns = j.at("columns").get<int32>();
}

static void to_json(nlohmann::json& j, const FIviTunerGridSize& p)
{
	j = nlohmann::json{{"rows", p.rows}, {"columns", p.columns}};
}
