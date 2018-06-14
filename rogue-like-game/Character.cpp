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

int sgn(int val) {
	return (0 < val) - (val < 0);
}

void Monster::make_move_to_knight(int knight_col, int knight_row, const std::shared_ptr<Map> map)
{
	int col_diff = abs(get_col() - knight_col);
	int row_diff = abs(get_row() - knight_row);
	if (col_diff < get_visibility() && row_diff < get_visibility()) {
		col_diff > row_diff ? move_to(sgn(knight_col - get_col()), 0, map) :
			col_diff < row_diff ? move_to(0, sgn(knight_row - get_row()), map) :
			rand() > RAND_MAX / 2 ? move_to(sgn(knight_col - get_col()), 0, map) : move_to(0, sgn(knight_row - get_row()), map);
	}
}
