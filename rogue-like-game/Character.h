#pragma once
#include <memory>
#include "Map.h"
#include "EventManager.h"

class Character;
class Knight;
class Wall;
class ActiveCharacter;
class EmptyFloor;
class Projectile;

class Character : public std::enable_shared_from_this<Character>
{
public:
	Character(int col, int row, char symbol = 'C', double damage = 0, double hp = INT_MAX) :
		_col(col), _row(row), _symbol(symbol), _damage(damage), _hp(hp) {};
	char get_symbol() const { return _symbol; }
	int get_col() { return _col; }
	int get_row() { return _row; }
	double get_damage() { return _damage; }
	double get_hp() { return _hp; }
	bool is_dead() { return _hp <= 0; }
	void set_pos(int col, int row) { _col = col; _row = row; }
	void take_damage(double damage) { _hp -= damage; }
	//virtual int get_dir_col() {}
	//virtual int get_dir_row() {}  ÊÎÍÑÒÀÍÒÍÛÅ ÌÅÒÎÄÛ ÑÄÅËÀÒÜ, ÊËÀÑÑ ÏÐÈÍÖÅÑÛ, ÌÅÒÎÄ ÎÁÐÀÁÎÒÊÈ ÕÎÄÀ ÃÅÐÎß
	virtual void move_to(int to_col, int to_row, const std::shared_ptr<Map> map) {}
	virtual bool may_step() { return true; }
	virtual void make_move_to_knight(int knight_col, int knight_row, const std::shared_ptr<Map> map) {};
	virtual void collide(Character &other, const std::shared_ptr<Map> map);
	virtual void collide(ActiveCharacter &other, const std::shared_ptr<Map> map);
	//virtual void collide(Knight &other, const std::shared_ptr<Map> map);
	virtual void collide(Projectile &other, const std::shared_ptr<Map> map);
	virtual void collide(EmptyFloor &other, const std::shared_ptr<Map> map);

	std::shared_ptr<Character> get_ptr() { return shared_from_this(); }

private:
	char _symbol;
	int _col, _row;
	double _damage, _hp;
};

class EmptyFloor : public Character 
{
public:
	EmptyFloor(int col, int row, char symbol = '.', double damage = 0, double hp = INT_MAX) :
		Character(col, row, symbol, damage, hp) {}
	void collide(Character &other, const std::shared_ptr<Map> map) override;
	virtual void collide(ActiveCharacter &other, const std::shared_ptr<Map> map);
	//virtual void collide(Knight &other, const std::shared_ptr<Map> map);
};

class ActiveCharacter : public Character 
{
public:
	ActiveCharacter(int col, int row, char symobol = 'A', double damage = 10, double hp = 100) : 
		Character(col, row, symobol, damage, hp) {}
	bool may_step() override { return false; }
	void move_to(int to_col, int to_row, const std::shared_ptr<Map> map);
	void collide(ActiveCharacter &other, const std::shared_ptr<Map> map) override;
	void collide(Character &other, const std::shared_ptr<Map> map) override;
	void collide(EmptyFloor &other, const std::shared_ptr<Map> map) override;
	void collide(Projectile &other, const std::shared_ptr<Map> map) override;
	void make_move_to_knight(int knight_col, int knight_row, const std::shared_ptr<Map> map) override {};
};

class Knight : public ActiveCharacter
{
public:
	Knight(int col, int row, char symbol = 'K', double damage = 10, double hp = 1000) : 
		ActiveCharacter(col, row, symbol, damage, hp) {};
	//void collide(Character &other, const std::shared_ptr<Map> map) override;
	void collide(ActiveCharacter &other, const std::shared_ptr<Map> map) override;

private:
	
};

class Monster : public ActiveCharacter
{
public:
	Monster(int col, int row, char symbol = 'M', int visibility = 5, double damage = 7, double hp = 100) :
		ActiveCharacter(col, row, symbol, damage, hp), _visibility(visibility) {};
	void collide(ActiveCharacter &other, const std::shared_ptr<Map> map) override;
	void make_move_to_knight(int knight_col, int knight_row, const std::shared_ptr<Map> map) override;
	int get_visibility() { return _visibility; }
private:
	int _visibility;
};

class Wall : public Character
{
public:
	Wall(int col, int row, char symbol = '#') : Character(col, row, symbol) {}
	void collide(Character &other, const std::shared_ptr<Map> map) override;
	void collide(Projectile &other, const std::shared_ptr<Map> map) override;
};

class Projectile : public ActiveCharacter
{
public:
	Projectile(int col, int row, char symbol = '0', double damage = 50, double hp = 1) 
		: ActiveCharacter(col, row, symbol, damage, hp) {}
	void collide(Character &other, const std::shared_ptr<Map> map) override;
	void collide(ActiveCharacter &other, const std::shared_ptr<Map> map) override;
	//int get_dir_col() override { return dir_to_col; }
	//int get_dir_row() override { return dir_to_row; }
private:
	int dir_to_col, dir_to_row;
};