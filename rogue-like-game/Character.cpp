#include "stdafx.h"
#include "Character.h"

void Character::�ollide(ActiveCharacter & other)
{
	this->�ollide(other);
}

void Character::collide(StaticCharacter & other)
{
	this->�ollide(other);
}

