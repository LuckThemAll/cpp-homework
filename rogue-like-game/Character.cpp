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

void Character::collide(Projectile & other, const std::shared_ptr<Map> map)
{
	other.collide(*this, map);
}

void Character::collide(EmptyFloor & other, const std::shared_ptr<Map> map)
{
	other.collide(*this, map);
}

void Character::collide(Princess & other, const std::shared_ptr<Map> map)
{
	other.collide(*this, map);
}

void Character::collide(HealCharacter & other, const std::shared_ptr<Map> map)
{
	other.collide(*this, map);
}

void Character::collide(Knight & other, const std::shared_ptr<Map> map)
{
//	other.collide(*this, map);
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

void ActiveCharacter::collide(Princess & other, const std::shared_ptr<Map> map)
{
	other.collide(*this, map);
}

void ActiveCharacter::collide(Projectile & other, const std::shared_ptr<Map> map)
{
	if (!other.is_dead()) {
		EventManager::get_manager().add_damage(other.get_ptr(), get_ptr(), other.get_damage());
		other.self_kill();
	}
	EventManager::get_manager().add_move(get_ptr(), other.get_col(), other.get_row());
}

void ActiveCharacter::collide(HealCharacter & other, const std::shared_ptr<Map> map)
{
	other.collide(*this, map);
}

void Knight::collide(ActiveCharacter & other, const std::shared_ptr<Map> map)
{
	EventManager::get_manager().add_damage(get_ptr(), other.get_ptr(), get_damage());
}

void Knight::collide(Princess & other, const std::shared_ptr<Map> map)
{
	other.collide(*this, map);
}

void Knight::collide(HealCharacter & other, const std::shared_ptr<Map> map)
{
	other.collide(*this, map);
}

void Knight::collide(Health & other, const std::shared_ptr<Map> map)
{
	other.collide(*this, map);
}

void Knight::collide(Mana & other, const std::shared_ptr<Map> map)
{
	other.collide(*this, map);
}

void Knight::set_dir(Direction dir)
{
	switch (dir) {
	case Direction::UP:
		set_dir_col(-1);
		set_dir_row(0);
		break;
	case Direction::DOWN:
		set_dir_col(1);
		set_dir_row(0);
		break;
	case Direction::RIGHT:
		set_dir_col(0);
		set_dir_row(1);
		break;
	case Direction::LEFT:
		set_dir_col(0);
		set_dir_row(-1);
		break;
	}
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
	other.collide(*this, map);
}

void Wall::collide(Projectile & other, const std::shared_ptr<Map> map)
{
	other.self_kill();
}

void Wall::collide(ActiveCharacter & other, const std::shared_ptr<Map> map)
{

}

int sgn(int val) {
	return (0 < val) - (val < 0);
}

void Monster::collide(ActiveCharacter & other, const std::shared_ptr<Map> map)
{
	EventManager::get_manager().add_damage(get_ptr(), other.get_ptr(), get_damage());
}

void Monster::collide(Princess & other, const std::shared_ptr<Map> map)
{
	//nothing
}

void Monster::collide(HealCharacter & other, const std::shared_ptr<Map> map)
{
	//nothing
}


void Monster::make_move_to_knight(int knight_col, int knight_row, const std::shared_ptr<Map> map)
{
	int col_diff = abs(get_col() - knight_col);
	int row_diff = abs(get_row() - knight_row);
	col_diff < get_visibility() && row_diff < get_visibility() ?
		col_diff > row_diff ? move_to(sgn(knight_col - get_col()), 0, map) :
		col_diff < row_diff ? move_to(0, sgn(knight_row - get_row()), map) :
		rand() > RAND_MAX / 2 ? move_to(sgn(knight_col - get_col()), 0, map) : move_to(0, sgn(knight_row - get_row()), map) :
		rand() > RAND_MAX / 2 ? rand() > RAND_MAX / 2 ? move_to(-1, 0, map) : move_to(1, 0, map) :
		rand() > RAND_MAX / 2 ? move_to(0, -1, map) : move_to(0, 1, map);
	
}

void Projectile::move_to(int to_col, int to_row, const std::shared_ptr<Map> map)
{
	if (map->is_inrange(get_col() + to_col, get_row() + to_row)) {
		auto cell = map->get_cell(get_col() + to_col, get_row() + to_row);
		auto character = cell->get_character();
		character->collide(*get_ptr(), map);
	}
	else self_kill();
}

void Projectile::collide(ActiveCharacter & other, const std::shared_ptr<Map> map)
{
	if (!other.is_dead()){
		EventManager::get_manager().add_damage(get_ptr(), other.get_ptr(), get_damage());
		self_kill();
	}
	else
		EventManager::get_manager().add_move(get_ptr(), other.get_col(), other.get_row());
}

void Projectile::collide(Character & other, const std::shared_ptr<Map> map)
{
	other.collide(*this, map);
}

void Projectile::collide(Princess & other, const std::shared_ptr<Map> map)
{
	self_kill();
}

void Projectile::collide(HealCharacter & other, const std::shared_ptr<Map> map)
{
	other.collide(*this, map);
}

void Princess::collide(Character & other, const std::shared_ptr<Map> map)
{
	other.collide(*this, map);
}

void Princess::collide(Knight & other, const std::shared_ptr<Map> map)
{
	other.set_pos(get_col(), get_row());
}

void HealCharacter::collide(Character & other, const std::shared_ptr<Map> map)
{
	other.collide(*this, map);
}

void HealCharacter::collide(Projectile & other, const std::shared_ptr<Map> map)
{
	if (!other.is_dead()) {
		self_kill();
		EventManager::get_manager().add_move(other.get_ptr(), get_col(), get_row());
	}
}

void HealCharacter::collide(ActiveCharacter & other, const std::shared_ptr<Map> map)
{
	other.collide(*this, map);
}

void HealCharacter::collide(Knight & other, const std::shared_ptr<Map> map)
{
	other.collide(*this, map);
}

void Health::collide(Knight & other, const std::shared_ptr<Map> map)
{
	other.heal(get_hp());
	EventManager::get_manager().add_move(other.get_ptr(), get_col(), get_row());
	self_kill();
}

void Mana::collide(Knight & other, const std::shared_ptr<Map> map)
{
	other.mana(get_hp());
	EventManager::get_manager().add_move(other.get_ptr(), get_col(), get_row());
	self_kill();
}
