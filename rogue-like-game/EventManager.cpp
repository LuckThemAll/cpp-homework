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
	_projectiles_spawn_events = std::make_shared<std::stack<std::shared_ptr<Event>>>();

	_events_pool.push_back(_move_events);
	_events_pool.push_back(_damage_events);
}

void EventManager::trigger_all(Game & game, std::shared_ptr<Map> map)
{
	for (auto& ev : _events_pool) {
		while (!ev->empty()) {
			ev->top()->trigger(game, map);
			ev->pop();
		}
	}
}

void EventManager::spawn_projectiles(Game & game, std::shared_ptr<Map> map)
{
	while (!_projectiles_spawn_events->empty()) {
		_projectiles_spawn_events->top()->trigger(game, map);
		_projectiles_spawn_events->pop();
		trigger_all(game, map);
	}
}

void EventManager::move_projectiles(Game & game, std::shared_ptr<Map> map)
{
	for (auto i = game.get_projectile_begin(); i != game.get_projectile_end();) {
		auto projectile = i->get();
		projectile->move_to(projectile->get_dir_col(), projectile->get_dir_row(), map);
		projectile->is_made_turn(true);
		trigger_all(game, map);

		if (projectile->is_dead()){
			map->move_character(projectile->get_col(), projectile->get_row(), 
				projectile->get_col(), projectile->get_row());
			i = game.erase_projectile(i);
		}
		else
			i++;
	}
}

void EventManager::add_projectile(std::shared_ptr<Projectile> projectile, int spawn_to_col, int spawn_to_row)
{
	auto a = new SpawnProjectileEvent(projectile, spawn_to_col, spawn_to_row);
	projectile->is_made_turn(true);
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

void MoveEvent::trigger(Game & game, std::shared_ptr<Map> map)
{
	_character->is_made_turn(true);
	if (map->is_inrange(_to_row, _to_col) || map->get_cell(_to_row, _to_col)->get_character()->is_dead()) {
		map->move_character(_character->get_col(), _character->get_row(),
			_to_col, _to_row);
	}
}

void DamageEvent::trigger(Game & game, std::shared_ptr<Map> map)
{
	_to->take_damage(_damage);
}

void SpawnProjectileEvent::trigger(Game & game, std::shared_ptr<Map> map)
{
	auto cell = map->get_cell(_spawn_to_col, _spawn_to_row);
	auto character = cell->get_character();
	if (character->is_transparent())
		map->spawn_character(_spawn_to_col, _spawn_to_row, _projectile);
	else
		character->collide(*_projectile, map);
	game.push_to_projectiles(_projectile);
	int a = 0;
}
