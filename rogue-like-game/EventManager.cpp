#include "stdafx.h"
#include "EventManager.h"

EventManager & EventManager::get_manager()
{
	static EventManager e;
	return e;
}

EventManager::EventManager()
{
	_move_events = std::make_shared<std::stack<std::shared_ptr<Event>>>();
	_damage_events = std::make_shared<std::stack<std::shared_ptr<Event>>>();
	_projectiles_move_events = std::make_shared<std::stack<std::shared_ptr<Event>>>();
	_projectiles_spawn_events = std::make_shared<std::stack<std::shared_ptr<Event>>>();

	_events_pool.push_back(_move_events);
	_events_pool.push_back(_damage_events);
	_events_pool.push_back(_projectiles_move_events);
	_events_pool.push_back(_projectiles_spawn_events);
}

void EventManager::trigger_all(std::shared_ptr<Map> map_)
{
	for (auto& ev : _events_pool) {
		while (!ev->empty()) {
			ev->top()->trigger(map_);
			ev->pop();
		}
	}
	int a = 0;
}

void EventManager::add_projectile(std::shared_ptr<Character> projectile, int spawn_to_col, int spawn_to_row)
{
	auto a = new SpawnProjectileEvent(projectile, spawn_to_col, spawn_to_row);
	_projectiles_spawn_events->emplace(a);
}

void EventManager::add_damage(std::shared_ptr<Character> from, std::shared_ptr<Character> to, double damage)
{
	auto a = new DamageEvent(from, to, damage);
	_damage_events->emplace(a);
}

void EventManager::add_move(std::shared_ptr<Character> character, int to_col, int to_row)
{
	auto a = new MoveEvent(character, to_col, to_row);
	_move_events->emplace(new MoveEvent(character, to_col, to_row));	
}

void MoveEvent::trigger(std::shared_ptr<Map> map)
{
	if (map->is_inrange(_to_row, _to_col) || map->get_cell(_to_row, _to_col)->get_character()->is_dead()) {
		map->move_character(_character->get_col(), _character->get_row(),
			_to_col, _to_row);
	}
}

void DamageEvent::trigger(std::shared_ptr<Map> map)
{
	_to->take_damage(_damage);
}

void SpawnProjectileEvent::trigger(std::shared_ptr<Map> map)
{
	auto cell = map->get_cell(_spawn_to_col, _spawn_to_row);
	auto character = cell->get_character();
	character->collide(*_projectile, map);

	map->spawn_character(_spawn_to_col, _spawn_to_row, _projectile);
}
