#pragma once

#include <vector>
#include "Character.h"
#include <algorithm>

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
	std::shared_ptr<MapCell> get_cell(int col, int row) { return _map[col][row]; }
	auto get_map() { return &_map; };
	int get_cols_num() { return _map.size(); }
	int get_rows_num() { return _map[0].size(); }
	bool is_inrange(int row, int col) { return get_cols_num() <= col && get_rows_num() <= row && col > -1 && row > -1; };
	void move_character(int from_col, int from_row, int to_col, int to_row, std::shared_ptr<Character> replace_actor = nullptr);
private:
	std::vector<std::vector<std::shared_ptr<MapCell>>> _map;
};


