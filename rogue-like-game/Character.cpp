#include "stdafx.h"
#include "Character.h"
#include "EventManager.h"

void Character::ñollide(ActiveCharacter & other, std::shared_ptr<Map> map)
{
	this->ñollide(other, map);
}

void Character::collide(StaticCharacter & other, std::shared_ptr<Map> map)
{
	this->ñollide(other, map);
}

void ActiveCharacter::move_to(int to_col, int to_row, std::shared_ptr<Map> map, EventManager event_manager)
{

}

void Knight::move_to(int to_col, int to_row, std::shared_ptr<Map> map, EventManager event_manager)
{
	event_manager.add_move(get_ptr(), to_col, to_row);
}
