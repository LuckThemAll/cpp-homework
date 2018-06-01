#include "stdafx.h"
#include "EventManager.h"

void EventManager::add_move(std::shared_ptr<Character> character, int to_row, int to_col)
{
	_move_events->emplace(new MoveEvent(character, to_row, to_col));
}

void MoveEvent::trigger(std::shared_ptr<Map>& map)
{
	if (map->is_inrange(_character->get_row() + _to_row, _character->get_col() + _to_col)) {
		map->move_character(_character->get_row(), _character->get_col(),
			_character->get_row() + _to_row, _character->get_col() + _to_col);
	}
}
