#pragma once

#include "Character.h"
#include "Map.h"
#include <stack>

class EventManager;
class Event;
class MoveEvent;
class DamageEvent;

class EventManager {
public:
	static EventManager &exemplar;

	//void trigger_all(std::vector<std::vector<std::shared_ptr<MapCell>>> &map);

	//void add_damage(std::shared_ptr<Character> from, std::shared_ptr<Character> to, double damage);
	//void add_move(std::shared_ptr<Character> character, Point to);

private:
	std::shared_ptr<std::stack<std::shared_ptr<Event>>> _move_events;
	std::shared_ptr<std::stack<std::shared_ptr<Event>>> _damage_events;
};

class Event {
public:
	virtual void trigger(std::vector<std::vector<std::shared_ptr<MapCell>>> &map) = 0;
};

class MoveEvent : public Event {
public:
	MoveEvent(std::shared_ptr<Character> character, int to_row, int to_col) 
		: _character(character), _to_row(to_row), _to_col(to_col)  {};

	//void trigger(std::vector<std::vector<std::shared_ptr<MapCell>>> &map) override;
private:
	std::shared_ptr<Character> _character;
	int _to_row, _to_col;
};

class DamageEvent : public Event {
public:
	DamageEvent(std::shared_ptr<Character> from, std::shared_ptr<Character> to, double damage) 
		: _from(from), _to(to), _damage(damage) {};

	//void trigger(std::vector<std::vector<std::shared_ptr<MapCell>>> &map) override;
private:
	std::shared_ptr<Character> _from;
	std::shared_ptr<Character> _to;
	double _damage;
};
