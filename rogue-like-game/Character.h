#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>


class ActiveCharacter;
class Character;
class StaticCharacter;
class Monster;
class Knight;
class Zombie;
class Zombie;

class Character : public std::enable_shared_from_this<Character>{
public:
	virtual void �ollide(Character &other) {};
	virtual void �ollide(ActiveCharacter &other);
	virtual void collide(StaticCharacter &other);
};

class ActiveCharacter : public Character {
public:
	void �ollide(Character &other) override { other.�ollide(*this); };
	void take_damage(double dmg) { _hp -= dmg; }
	double get_damage() { return _dmg; }
protected:
	double _hp;
	double _dmg;
};

class StaticCharacter : public Character {
	void �ollide(Character &other) override { other.�ollide(*this); };
};

class Knight : public ActiveCharacter {
public:
	void �ollide(Character &other) override { other.�ollide(*this); };
	void collide(Monster &other);
};

class Monster : public ActiveCharacter {
	void �ollide(Character &other) override { other.�ollide(*this); };
	void collide(Monster &other);
};

class Zombie : public ActiveCharacter {

};

