#include "stdafx.h"
#include "Character.h"
#include "EventManager.h"

void Character::ñollide(ActiveCharacter & other)
{
	this->ñollide(other);
}

void Character::collide(StaticCharacter & other)
{
	this->ñollide(other);
}

void ActiveCharacter::move_to(std::shared_ptr<Map> map, int to_col, int to_row, EventManager event_manager)
{

}

void Knight::move_to(std::shared_ptr<Map> map, int to_col, int to_row, EventManager event_manager)
{
	event_manager.add_move(get_ptr(), to_col, to_row);
}
