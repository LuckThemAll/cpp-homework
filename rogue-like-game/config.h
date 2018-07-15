#pragma once
#include <nlohmann\json.hpp>

class Config {
public:
	Config();
	nlohmann::json json() const { return _json; }
	std::string get_symbol_str() const { return _symbol_str; }
	std::string get_hp_str() const { return _hp_str; }
	std::string get_character_str() const { return _character_str; }
	std::string get_damage_str() const { return _damage_str; }

private:
	std::string _symbol_str = "symbol";
	std::string _hp_str = "hp";
	std::string _damage_str = "damage";
	std::string _character_str = "Character";
	nlohmann::json _json;
};