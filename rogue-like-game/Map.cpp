#include "stdafx.h"
#include "Map.h"

void Map::set_cell(int col, int row, std::shared_ptr<MapCell> cell)
{
	_map[col][row] = cell;
}

void Map::move_character(int from_col, int from_row, int to_col, int to_row, std::shared_ptr<Character> replace_actor)
{
	replace_actor = std::make_shared<EmptyFloor>(from_col, from_row);

	get_cell(to_col, to_row)->set_character(get_cell(from_col, from_row)->get_character());
	get_cell(to_col, to_row)->get_character()->set_pos(to_col, to_row);

	get_cell(from_col, from_row)->set_character(replace_actor);
	get_cell(from_col, from_row)->get_character()->set_pos(from_col, from_row);


	/*std::shared_ptr<Character> temp_character = _map[from_col][from_row]->get_character();
	_map[from_col][from_row]->set_character(_map[to_col][to_row]->get_character());
	_map[to_col][to_row]->set_character(temp_character);*/
}
