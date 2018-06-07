#include "stdafx.h"
#include "EventManager.h"

EventManager::EventManager()
{
	
	_move_events = std::make_shared<std::stack<std::shared_ptr<Event>>>();

	_events_pool.push_back(_move_events);
	//std::make_shared<std::stack<std::shared_ptr<Event>>>;
}

void EventManager::trigger_all(std::shared_ptr<Map> map_)
{
	for (auto& ev : _events_pool) {
		while (!ev->empty()) {
			ev->top()->trigger(map_);
			ev->pop();
		}
	}
}

void EventManager::add_move(std::shared_ptr<Character> character, int to_col, int to_row)
{
	//_move_events->emplace(std::make_shared<MoveEvent>(character, to_row, to_col));

	_move_events->emplace(new MoveEvent(character, to_col, to_row));	
}

void MoveEvent::trigger(std::shared_ptr<Map> map)
{
	int c = map->get_cols_num(); // тут все нормально
	if (map->is_inrange(_character->get_row() + _to_row, _character->get_col() + _to_col)) {
		map->move_character(_character->get_col(), _character->get_row(),
			_character->get_col() + _to_col, _character->get_row() + _to_row);
	}
}
