#include "stdafx.h"
#include "Character.h"

void Character::�ollide(ActiveCharacter & other)
{
	this->�ollide(*static_cast<Character*>(&other));
}

void Character::collide(StaticCharacter & other)
{
	this->�ollide(*static_cast<Character*>(&other));
}

void Knight::collide(Monster & other)
{
	take_damage(other.get_damage());
}

void Monster::collide(Monster & other)
{
	take_damage(other.get_damage());
}
