#include "stdafx.h"
#include "Character.h"

void Character::collide(Character & other, const std::shared_ptr<Map> map)
{
}

void Character::collide(Knight & other, const std::shared_ptr<Map> map)
{
}

void Knight::move_to(int to_col, int to_row, const std::shared_ptr<Map> map)
{
}

void Knight::collide(Character & other, const std::shared_ptr<Map> map)
{
}
