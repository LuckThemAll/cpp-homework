#pragma once
#include <memory>
#include "Map.h"
#include "EventManager.h"

class Character;
class Knight;
class Wall;

class Character : public std::enable_shared_from_this<Character>
{
public:
	Character(int col, int row, char symbol) : _col(col), _row(row), _symbol(symbol) {};
	char get_symbol() const { return _symbol; }
	int get_col() { return _col; }
	int get_row() { return _row; }
	void set_pos(int col, int row) { _col = col; _row = row; }
	virtual void collide(Character &other, const std::shared_ptr<Map> map);
	virtual void collide(Knight &other, const std::shared_ptr<Map> map);
	std::shared_ptr<Character> get_ptr() { return shared_from_this(); }

private:
	char _symbol;
	int _col, _row;

};

class Knight : public Character
{
public:
	Knight(int col, int row) : Character(col, row, 'K') {};
	void move_to(int to_col, int to_row, const std::shared_ptr<Map> map);
	void collide(Character &other, const std::shared_ptr<Map> map) override;
private:
	
};

class Wall : public Character
{
public:
	Wall(int col, int row) : Character(col, row, '#') {}
	void collide(Character &other, const std::shared_ptr<Map> map) override {}
};