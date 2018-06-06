#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Map.h"
#include "EventManager.h"


class ActiveCharacter;
class Character;
class StaticCharacter;
class Monster;
class Knight;
class Zombie;
class Zombie;
class EventManager;

class Map; 



class Character : public std::enable_shared_from_this<Character> {
public:
	virtual void ñollide(Character &other) {};
	virtual void ñollide(ActiveCharacter &other);
	virtual void collide(StaticCharacter &other);
	virtual char get_sign() = 0;
	int get_col() { return _col; }
	int get_row() { return _row; }
	std::shared_ptr<Character> get_ptr() { return shared_from_this(); };
protected:
	int _col, _row;

};

class ActiveCharacter : public Character {
public:
	ActiveCharacter() {};
	char get_sign() override { return 'A'; };
	void ñollide(Character &other) override { other.ñollide(*this); };
	void take_damage(double dmg) { _hp -= dmg; }
	double get_damage() { return _dmg; }
	virtual void move_to(std::shared_ptr<Map> map, int to_col, int to_row, EventManager event_manager) = 0;
protected:
	double _hp;
	double _dmg;
};

class StaticCharacter : public Character {
public:
	void ñollide(Character &other) override { other.ñollide(*this); };
	char get_sign() override { return '.'; };
};

class Knight : public ActiveCharacter {
public:
	void ñollide(Character &other) override { other.ñollide(*this); };
	void move_to(std::shared_ptr<Map> map, int to_col, int to_row, EventManager event_manager) override;
	char get_sign() override { return 'K'; };
	//void collide(Monster &other);
};

class Monster : public ActiveCharacter {
	void ñollide(Character &other) override { other.ñollide(*this); };
	//void collide(Monster &other);
};

class Zombie : public ActiveCharacter {

};

class Floor : public StaticCharacter {
	char get_sign() override { return '.'; };
};

class EmptyFloor : public Floor {
	char get_sign() override { return '.'; };
};