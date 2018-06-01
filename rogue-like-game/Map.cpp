#include "stdafx.h"
#include "Map.h"

void Map::move_character(int from_row, int from_col, int to_row, int to_col)
{
	std::shared_ptr<Character> temp_character = _map[from_row][from_col]->get_character();
	_map[from_row][from_col]->set_character(_map[to_row][to_col]->get_character());
	_map[to_row][to_col]->set_character(temp_character);
}
