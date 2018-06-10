#include "stdafx.h"
#include "Character.h"

void Character::collide(Character & other, const std::shared_ptr<Map> map)
{
	EventManager::instance().add_move(other.get_ptr(), get_col(), get_row());
}

void Character::collide(Knight & other, const std::shared_ptr<Map> map)
{
	int debug2 = 0;
}

void Knight::move_to(int to_col, int to_row, const std::shared_ptr<Map> map)
{
	if (map->is_inrange(get_col() + to_col, get_row() + to_row)){
		map->get_cell(get_col() + to_col, get_row() + to_row)->get_character()->collide(*get_ptr(), map);
	}
}

void Knight::collide(Character & other, const std::shared_ptr<Map> map)
{
	int debug3 = 0;
}
