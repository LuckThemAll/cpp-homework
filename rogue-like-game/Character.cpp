#include "stdafx.h"
#include "Character.h"

void Character::collide(Character & other, const std::shared_ptr<Map> map)
{
	other.collide(*this, map);

}

void Character::collide(ActiveCharacter & other, const std::shared_ptr<Map> map)
{
	int debug = 0;
}

void Character::collide(Knight & other, const std::shared_ptr<Map> map)
{
	int debug = 0;
}

void ActiveCharacter::move_to(int to_col, int to_row, const std::shared_ptr<Map> map)
{
	if (map->is_inrange(get_col() + to_col, get_row() + to_row)){
		auto c = map->get_cell(get_col() + to_col, get_row() + to_row);
		auto ca = c->get_character();
		ca->collide(*get_ptr(), map);
	}
}

void ActiveCharacter::collide(Character & other, const std::shared_ptr<Map> map)
{
	int debug3 = 0;
}

void Knight::collide(Character & other, const std::shared_ptr<Map> map)
{
	other.collide(*this, map);
}

void EmptyFloor::collide(ActiveCharacter & other, const std::shared_ptr<Map> map)
{
	int debug = 0;
}

void EmptyFloor::collide(Knight & other, const std::shared_ptr<Map> map)
{
	EventManager::get_manager().add_move(other.get_ptr(), get_col(), get_row());
}

void Wall::collide(Character & other, const std::shared_ptr<Map> map)
{
	//nothing
	int debug = 0;
}
