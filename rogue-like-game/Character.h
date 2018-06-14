#pragma once
#include <memory>
#include "Map.h"
#include "EventManager.h"

class Character;
class Knight;
class Wall;
class ActiveCharacter;
class EmptyFloor;

class Character : public std::enable_shared_from_this<Character>
{
public:
	Character(int col, int row, char symbol) : _col(col), _row(row), _symbol(symbol) {};
	char get_symbol() const { return _symbol; }
	int get_col() { return _col; }
	int get_row() { return _row; }
	void set_pos(int col, int row) { _col = col; _row = row; }
	virtual bool may_step() { return true; }
	virtual void make_move(const std::shared_ptr<Map> map) {};
	virtual void collide(Character &other, const std::shared_ptr<Map> map);
	virtual void collide(ActiveCharacter &other, const std::shared_ptr<Map> map);
	virtual void collide(Knight &other, const std::shared_ptr<Map> map);
	virtual void collide(EmptyFloor &other, const std::shared_ptr<Map> map);

	std::shared_ptr<Character> get_ptr() { return shared_from_this(); }

private:
	char _symbol;
	int _col, _row;

};

class EmptyFloor : public Character 
{
public:
	EmptyFloor(int col, int row, char symbol = 'q') : Character(col, row, '.') {}
	void collide(Character &other, const std::shared_ptr<Map> map) override;
	virtual void collide(ActiveCharacter &other, const std::shared_ptr<Map> map);
	//virtual void collide(Knight &other, const std::shared_ptr<Map> map);
};

class ActiveCharacter : public Character 
{
public:
	ActiveCharacter(int col, int row, char symobol = 'A') : Character(col, row, symobol) {}
	bool may_step() override { return false; }
	void move_to(int to_col, int to_row, const std::shared_ptr<Map> map);
	void collide(ActiveCharacter &other, const std::shared_ptr<Map> map) override;
	void collide(Character &other, const std::shared_ptr<Map> map) override;
	void collide(EmptyFloor &other, const std::shared_ptr<Map> map) override;
	void make_move(const std::shared_ptr<Map> map) override {};
};

class Knight : public ActiveCharacter
{
public:
	Knight(int col, int row) : ActiveCharacter(col, row, 'K') {};
	void collide(Character &other, const std::shared_ptr<Map> map) override;
private:
	
};

class Monster : public ActiveCharacter
{
public:
	Monster(int col, int row) : ActiveCharacter(col, row, 'M') {};
	void make_move(const std::shared_ptr<Map> map) override;
};

class Wall : public Character
{
public:
	Wall(int col, int row) : Character(col, row, '#') {}
	void collide(Character &other, const std::shared_ptr<Map> map) override;
};