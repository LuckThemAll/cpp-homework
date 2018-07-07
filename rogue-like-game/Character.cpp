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

void Character::collide(Health & other, const std::shared_ptr<Map> map)
{
	other.collide(*this, map);
}

void Character::collide(Mana & other, const std::shared_ptr<Map> map)
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

void ActiveCharacter::collide(Princess & other, const std::shared_ptr<Map> map)
{
	other.collide(*this, map);
}

void ActiveCharacter::collide(Projectile & other, const std::shared_ptr<Map> map)
{
	if (!other.is_dead()) {
		EventManager::get_manager().add_damage(other.get_ptr(), get_ptr(), other.get_damage());
		other.kill();
	}
	EventManager::get_manager().add_move(get_ptr(), other.get_col(), other.get_row());
}

void ActiveCharacter::collide(Health & other, const std::shared_ptr<Map> map)
{
	other.collide(*this, map);
}

void ActiveCharacter::collide(Mana & other, const std::shared_ptr<Map> map)
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

void Knight::collide(Health & other, const std::shared_ptr<Map> map)
{
	heal(other.get_hp());
	EventManager::get_manager().add_move(get_ptr(), other.get_col(), other.get_row());
	other.kill();
}

void Knight::collide(Mana & other, const std::shared_ptr<Map> map)
{
	mana(other.get_hp());
	EventManager::get_manager().add_move(get_ptr(), other.get_col(), other.get_row());
	other.kill();
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
	other.kill();
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

void Monster::collide(Health & other, const std::shared_ptr<Map> map)
{
	//nothing
}

void Monster::collide(Mana & other, const std::shared_ptr<Map> map)
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
	else kill();
}

void Projectile::collide(ActiveCharacter & other, const std::shared_ptr<Map> map)
{
	if (!other.is_dead()){
		EventManager::get_manager().add_damage(get_ptr(), other.get_ptr(), get_damage());
		kill();
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
	kill();
}

void Projectile::collide(Health & other, const std::shared_ptr<Map> map)
{
	other.collide(*this, map);
}

void Projectile::collide(Mana & other, const std::shared_ptr<Map> map)
{
	other.collide(*this, map);
}

void Princess::collide(Character & other, const std::shared_ptr<Map> map)
{
	other.collide(*this, map);
}

void Princess::collide(Knight & other, const std::shared_ptr<Map> map)
{
	other.set_win();
}

void Health::collide(Character & other, const std::shared_ptr<Map> map)
{
	other.collide(*this, map);
}

void Health::collide(Projectile & other, const std::shared_ptr<Map> map)
{
	if (!other.is_dead()) {
		kill();
		EventManager::get_manager().add_move(other.get_ptr(), get_col(), get_row());
	}
}

void Health::collide(ActiveCharacter & other, const std::shared_ptr<Map> map)
{
	other.collide(*this, map);
}

void Mana::collide(Character & other, const std::shared_ptr<Map> map)
{
	other.collide(*this, map);
}

void Mana::collide(Projectile & other, const std::shared_ptr<Map> map)
{
	if (!other.is_dead()) {
		kill();
		EventManager::get_manager().add_move(other.get_ptr(), get_col(), get_row());
	}
}

void Mana::collide(ActiveCharacter & other, const std::shared_ptr<Map> map)
{
	other.collide(*this, map);
}
