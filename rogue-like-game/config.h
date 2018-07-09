#pragma once
#include <nlohmann\json.hpp>

class Config {
public:
	Config();
	nlohmann::json json() const { return _json; }

private:
	nlohmann::json _json;
};