#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
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
	Character() {};
	Character(int col, int row) : _col(col), _row(row) {};
	virtual void ñollide(Character &other, std::shared_ptr<Map> map) {};
	virtual void ñollide(ActiveCharacter &other, std::shared_ptr<Map> map);
	virtual void collide(StaticCharacter &other, std::shared_ptr<Map> map);
	virtual char const get_sign() = 0;

	int get_col() { return _col; }
	int get_row() { return _row; }
	void set_col(int col) { _col = col; };
	void set_row(int row) { _row = row; };
	void set_pos(int col, int row) { set_col(col); set_row(row); };
	std::shared_ptr<Character> get_ptr() { return shared_from_this(); };
protected:
	int _col, _row;

};

class ActiveCharacter : public Character {
public:
	ActiveCharacter() {};
	ActiveCharacter(int col, int row) : Character(col, row) {};
	char const get_sign() override { return 'A'; };
	void ñollide(Character &other, std::shared_ptr<Map> map) override { other.ñollide(*this, map); };
	void take_damage(const double dmg) { _hp -= dmg; }
	double const get_damage() { return _dmg; }
	virtual void move_to(const int to_col, int to_row, std::shared_ptr<Map> map, EventManager event_manager) = 0;
protected:
	double _hp;
	double _dmg;
};

class Knight : public ActiveCharacter {
public:
	Knight() {};
	Knight(int col, int row) : ActiveCharacter(col, row) {};
	void ñollide(Character &other, std::shared_ptr<Map> map) override { other.ñollide(*this, map); };
	void move_to(int to_col, int to_row, std::shared_ptr<Map> map, EventManager event_manager) override;
	char const get_sign() override { return 'K'; };
	//void collide(Monster &other);
};

class StaticCharacter : public Character {
public:
	StaticCharacter() {};
	StaticCharacter(int col, int row) : Character(col, row) {};
	void ñollide(Character &other, std::shared_ptr<Map> map) override { other.ñollide(*this, map); };
	char const get_sign() override { return '.'; };
};

class Floor : public StaticCharacter {
public:
	Floor() {};
	Floor(int col, int row) : StaticCharacter(col, row) {};
	char const get_sign() override { return '.'; };
};

class Lava : public StaticCharacter {
public:
	Lava() {};
	Lava(int col, int row) : StaticCharacter(col, row) {};
	char const get_sign() override { return '.'; };
};

class EmptyFloor : public Floor {
public:
	EmptyFloor() {};
	EmptyFloor(int col, int row) : Floor(col, row) {};
	char const get_sign() override { return '.'; };
};

class Monster : public ActiveCharacter {
public:
	Monster() {};
	void ñollide(Character &other, std::shared_ptr<Map> map) override { other.ñollide(*this, map); };
	//void collide(Monster &other);
};

class Zombie : public ActiveCharacter {
public:
	Zombie() {};
};