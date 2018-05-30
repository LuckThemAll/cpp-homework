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
	virtual void ñollide(Character &other) {};
	virtual void ñollide(ActiveCharacter &other);
	virtual void collide(StaticCharacter &other);
};

class ActiveCharacter : public Character {
public:
	void ñollide(Character &other) override { other.ñollide(*this); };
	void take_damage(double dmg) { _hp -= dmg; }
	double get_damage() { return _dmg; }
protected:
	double _hp;
	double _dmg;
};

class StaticCharacter : public Character {
	void ñollide(Character &other) override { other.ñollide(*this); };
};

class Knight : public ActiveCharacter {
public:
	void ñollide(Character &other) override { other.ñollide(*this); };
	void collide(Monster &other);
};

class Monster : public ActiveCharacter {
	void ñollide(Character &other) override { other.ñollide(*this); };
	void collide(Monster &other);
};

class Zombie : public ActiveCharacter {

};

