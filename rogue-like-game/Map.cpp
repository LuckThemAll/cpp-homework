#include "stdafx.h"
#include "Map.h"

void Map::set_cell(int col, int row, std::shared_ptr<MapCell> cell)
{
	_map[col][row] = cell;
}

bool Map::is_inrange(int col, int row)
{
	return get_cols_num() > col && get_rows_num() > row && col > -1 && row > -1;
}

void Map::spawn_character(int to_col, int to_row, std::shared_ptr<Character> spawn_character)
{
	if (!get_cell(to_col, to_row)->get_character()->is_transparent() && !get_cell(to_col, to_row)->get_character()->is_dead())
		return;
	get_cell(to_col, to_row)->set_character(spawn_character);
	get_cell(to_col, to_row)->get_character()->set_pos(to_col, to_row);
}

void Map::move_character(int from_col, int from_row, int to_col, int to_row, std::shared_ptr<Character> replace_character)
{
	if (!get_cell(to_col, to_row)->get_character()->is_transparent() && !get_cell(to_col, to_row)->get_character()->is_dead())
		return;
	if (!replace_character) {
		replace_character = std::make_shared<EmptyFloor>(from_col, from_row, '.');
	}
	get_cell(to_col, to_row)->set_character(get_cell(from_col, from_row)->get_character());
	get_cell(to_col, to_row)->get_character()->set_pos(to_col, to_row);

	get_cell(from_col, from_row)->set_character(replace_character);
	get_cell(from_col, from_row)->get_character()->set_pos(from_col, from_row);
}
