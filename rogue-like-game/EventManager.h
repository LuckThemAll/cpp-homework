#pragma once

#include "Game.h"
#include "Character.h"
#include <stack>

class EventManager;
class Event;
class MoveEvent;
class DamageEvent;
class SpawnProjectileEvent;
class Character;
class Projectile;
class Map;
class Game;

class EventManager 
{
public:
	static EventManager& get_manager();
	EventManager();
	void trigger_all(Game & game, std::shared_ptr<Map> map);
	void spawn_projectiles(Game & game, std::shared_ptr<Map> map);
	void move_projectiles(Game & game, std::shared_ptr<Map> map);
	void add_projectile(std::shared_ptr<Projectile> projectile, int spawn_to_col, int spawn_to_row);
	void add_damage(std::shared_ptr<Character> from, std::shared_ptr<Character> to, double damage);
	void add_move(std::shared_ptr<Character> character, int to_row, int to_col);
private:
	std::shared_ptr<std::stack<std::shared_ptr<Event>>> _move_events;
	std::shared_ptr<std::stack<std::shared_ptr<Event>>> _damage_events;
	std::shared_ptr<std::stack<std::shared_ptr<Event>>> _projectiles_spawn_events;

	std::vector<std::shared_ptr<std::stack<std::shared_ptr<Event>>>> _events_pool;
};

class Event {
public:
	virtual void trigger(Game & game, std::shared_ptr<Map> map) = 0;
};

class MoveEvent : public Event 
{
public:
	MoveEvent(std::shared_ptr<Character> character, int to_col, int to_row) 
		: _character(character), _to_row(to_row), _to_col(to_col)  {}

	void trigger(Game & game, std::shared_ptr<Map> map) override;
private:
	std::shared_ptr<Character> _character;
	int _to_row, _to_col;
};

class DamageEvent : public Event 
{
public:
	DamageEvent(std::shared_ptr<Character> from, std::shared_ptr<Character> to, double damage) 
		: _from(from), _to(to), _damage(damage) {}

	void trigger(Game & game, std::shared_ptr<Map> map) override;
private:
	std::shared_ptr<Character> _from;
	std::shared_ptr<Character> _to;
	double _damage;
};

class SpawnProjectileEvent : public Event
{
public:
	SpawnProjectileEvent(std::shared_ptr<Projectile> projectile, int spawn_to_col, int spawn_to_row)
		: _projectile(projectile), _spawn_to_row(spawn_to_row), _spawn_to_col(spawn_to_col) {}

	void trigger(Game & game, std::shared_ptr<Map> map);
private:
	std::shared_ptr<Projectile> _projectile;
	int _spawn_to_row, _spawn_to_col;
};