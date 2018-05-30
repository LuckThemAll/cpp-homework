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
	static EventManager& exemplar;

	void trigger_all(std::shared_ptr<Map> map);

	void add_damage(std::shared_ptr<Character> from, std::shared_ptr<Character> to, double damage);
	void add_move(std::shared_ptr<Character> character, Point to);

private:
	std::shared_ptr<std::stack<std::shared_ptr<Event>>> _move_events;
	std::shared_ptr<std::stack<std::shared_ptr<Event>>> _damage_events;
};

class Event {
public:
	virtual void trigger(std::shared_ptr<Map> map) = 0;
};

class MoveEvent : public Event {
public:
	MoveEvent(std::shared_ptr<Character> character, Point to) : _character(character), _to(to) {};

	void trigger(std::shared_ptr<Map> map) override;
private:
	std::shared_ptr<Character> _character;
	Point _to;
};

class DamageEvent : public Event {
public:
	DamageEvent(std::shared_ptr<Character> from, std::shared_ptr<Character> to, double damage) 
		: _from(from), _to(to), _damage(damage) {};

	void trigger(std::shared_ptr<Map> map) override;
private:
	std::shared_ptr<Character> _from;
	std::shared_ptr<Character> _to;
	double _damage;
};
