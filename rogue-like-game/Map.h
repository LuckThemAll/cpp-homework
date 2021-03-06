#pragma once

#include <vector>
#include "Character.h"
#include <algorithm>

class Map;
class MapCell;
class StaticCharacter;
class ActiveCharacter;
class Character;

class MapCell 
{
public:
	MapCell(std::shared_ptr<Character> floor, std::shared_ptr<Character> character)
		: _floor(floor), _character(character) {}
	void set_character(std::shared_ptr<Character> character) { _character = character; }
	void set_floor(std::shared_ptr<Character> floor) { _floor = floor; }
	std::shared_ptr<Character> get_character() { return _character; }
	std::shared_ptr<Character> get_floor() { return _floor; }

private:
	std::shared_ptr<Character> _floor;
	std::shared_ptr<Character> _character;
};

class Map 
{
public:
	Map() {}
	Map(std::vector<std::vector<std::shared_ptr<MapCell>>> map) : _map(map) {}
	std::shared_ptr<MapCell> get_cell(int col, int row) { return _map[col][row]; }
	void clear_map();
	void set_cell(int col, int row, std::shared_ptr<MapCell> cell);
	auto get_map() { return &_map; }
	int get_cols_num() { return (_map.size()); }
	int get_rows_num() { return (_map[0].size()); }
	std::vector<std::shared_ptr<MapCell>> &get_col(int col) { return _map[col]; }
	bool is_inrange(int col, int row);
	void spawn_character(int to_col, int to_row, std::shared_ptr<Character> spawn_character);
	void move_character(int from_col, int from_row, int to_col, int to_row, std::shared_ptr<Character> replace_actor = nullptr);
private:
	std::vector<std::vector<std::shared_ptr<MapCell>>> _map;
};


