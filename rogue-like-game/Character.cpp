#include "stdafx.h"
#include "Character.h"

void Character::collide(Character & other, const std::shared_ptr<Map> map)
{
	other.collide(*this, map);

}

void Character::collide(ActiveCharacter & other, const std::shared_ptr<Map> map)
{
	other.collide(*this, map);
}

void Character::collide(EmptyFloor & other, const std::shared_ptr<Map> map)
{
	other.collide(*this, map);
}

void ActiveCharacter::move_to(int to_col, int to_row, const std::shared_ptr<Map> map)
{
	if (map->is_inrange(get_col() + to_col, get_row() + to_row)){
		auto cell = map->get_cell(get_col() + to_col, get_row() + to_row);
		auto character = cell->get_character();
		character->collide(*get_ptr(), map);
	}
}

void ActiveCharacter::collide(ActiveCharacter & other, const std::shared_ptr<Map> map)
{
	other.collide(*this, map);
}

void ActiveCharacter::collide(Character & other, const std::shared_ptr<Map> map)
{
	other.collide(*this, map);
}

void ActiveCharacter::collide(EmptyFloor & other, const std::shared_ptr<Map> map)
{
	other.collide(*this, map);
}

void Knight::collide(ActiveCharacter & other, const std::shared_ptr<Map> map)
{
	//take_damage from ActiveCharacter;
}

void EmptyFloor::collide(Character & other, const std::shared_ptr<Map> map)
{
	other.collide(*this, map);
}

void EmptyFloor::collide(ActiveCharacter & other, const std::shared_ptr<Map> map)
{
	EventManager::get_manager().add_move(other.get_ptr(), get_col(), get_row());
}

void Wall::collide(Character & other, const std::shared_ptr<Map> map)
{
	//nothing
	int debug = 0;
}

void Monster::make_move_to_knight(int knight_col, int knight_row, const std::shared_ptr<Map> map)
{
	if (abs(get_col() - knight_col) < 5 && abs(get_row() - knight_row) < 5) {
		//дописать хождение монтсра к игроку, хп, дамаг
		if (knight_col - get_col) {
			move_to(-1, 0, map);
		}
	}
	move_to(-1, -1, map);
}
