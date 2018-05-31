#pragma once

#include <vector>
#include "Character.h"

class Map;
class MapCell;
class StaticCharacter;
class ActiveCharacter;
class Character;

class MapCell {
public:
	MapCell(std::shared_ptr<StaticCharacter> floor, std::shared_ptr<Character> character) 
		: _floor(floor), _character(character) {};
	void set_character(std::shared_ptr<Character> character) { _character = character; };
	void set_floor(std::shared_ptr<StaticCharacter> floor) { _floor = floor; };
	std::shared_ptr<Character> get_character() { return _character; };
	std::shared_ptr<StaticCharacter> get_floor() { return _floor; };

private:
	std::shared_ptr<StaticCharacter> _floor;
	std::shared_ptr<Character> _character;
};

class Map {
public:
	Map(std::vector<std::vector<std::shared_ptr<MapCell>>> map) : _map(map) {};
	std::shared_ptr<MapCell> get_cell(int col, int row) { return _map[row][col]; }
	auto get_map() { return &_map; };
private:
	std::vector<std::vector<std::shared_ptr<MapCell>>> _map;
};


