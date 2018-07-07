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
class Princess;
class Monster;
class Map;
class Health;
class Mana;

class Character : public std::enable_shared_from_this<Character>
{
public:
	Character(int col, int row, char symbol = 'C', double damage = 0, double hp = INT_MAX, bool is_made_turn = false) :
		_col(col), _row(row), _symbol(symbol), _damage(damage), _hp(hp), _is_made_turn(is_made_turn) {};
	char get_symbol() const { return _symbol; }
	int get_col() const { return _col; }
	int get_row() const { return _row; }
	double get_damage() const { return _damage; }
	double get_hp() const { return _hp; }
	bool is_dead() { return _hp <= 0; }
	void set_pos(int col, int row) { _col = col; _row = row; }
	void take_damage(double damage) { _hp -= damage; }
	void kill() { _hp = 0; };
	void heal(double hp) { _hp += hp; }
	void is_made_turn(bool result) { _is_made_turn = result; };
	bool is_made_turn() const { return _is_made_turn; }
	virtual double mana() { return 0; }
	virtual double cost() { return 0; };
	virtual void mana(double mana) {};
	virtual void set_dir_to_col(int to_col) { _dir_to_col = to_col; }
	virtual void set_dir_to_row(int to_row) { _dir_to_row = to_row; }
	virtual void set_dir(int to_col, int to_row) { set_dir_to_col(to_col); set_dir_to_row(to_row); }
	virtual int get_dir_col() const { return _dir_to_col; }
	virtual int get_dir_row() const { return _dir_to_row; }
	virtual void move_to(int to_col, int to_row, const std::shared_ptr<Map> map) {}
	virtual bool is_transparent() { return true; }
	virtual void make_move_to_knight(int knight_col, int knight_row, const std::shared_ptr<Map> map) {};
	virtual void collide(Character &other, const std::shared_ptr<Map> map);
	virtual void collide(ActiveCharacter &other, const std::shared_ptr<Map> map);
	virtual void collide(Projectile &other, const std::shared_ptr<Map> map);
	virtual void collide(EmptyFloor &other, const std::shared_ptr<Map> map);
	virtual void collide(Princess &other, const std::shared_ptr<Map> map);
	virtual void collide(Health &other, const std::shared_ptr<Map> map);
	virtual void collide(Mana &other, const std::shared_ptr<Map> map);
	
	std::shared_ptr<Character> get_ptr() { return shared_from_this(); }
protected:
	bool _is_made_turn;
private:
	int _dir_to_col, _dir_to_row;
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
	virtual void collide(Projectile &other, const std::shared_ptr<Map> map) {};
};

class ActiveCharacter : public Character 
{
public:
	ActiveCharacter(int col, int row, char symobol = 'A', double damage = 10, double hp = 100, bool is_made_turn = false) :
		Character(col, row, symobol, damage, hp, is_made_turn) {}
	bool is_transparent() override { return false; }
	void move_to(int to_col, int to_row, const std::shared_ptr<Map> map);
	void collide(ActiveCharacter &other, const std::shared_ptr<Map> map) override;
	void collide(Character &other, const std::shared_ptr<Map> map) override;
	void collide(EmptyFloor &other, const std::shared_ptr<Map> map) override;
	void collide(Princess &other, const std::shared_ptr<Map> map) override;
	void collide(Projectile &other, const std::shared_ptr<Map> map) override;
	void collide(Health &other, const std::shared_ptr<Map> map) override;
	void collide(Mana &other, const std::shared_ptr<Map> map) override;
	void make_move_to_knight(int knight_col, int knight_row, const std::shared_ptr<Map> map) override {};
};

class Knight : public ActiveCharacter
{
public:
	Knight(int col, int row, char symbol = 'K', double damage = 10, double hp = 1000) : 
		ActiveCharacter(col, row, symbol, damage, hp), _is_winner(false), _mana(500) {};
	void collide(ActiveCharacter &other, const std::shared_ptr<Map> map) override;
	void collide(Princess &other, const std::shared_ptr<Map> map);
	void collide(Health &other, const std::shared_ptr<Map> map) override;
	void collide(Mana &other, const std::shared_ptr<Map> map) override;
	void set_win() { _is_winner = true; };
	double mana() override { return _mana; }
	void mana(double mana) override { _mana += mana; }
	bool is_winner() const { return _is_winner; }
private:
	bool _is_winner;
	double _mana;
};

class Princess : public ActiveCharacter
{
public:
	Princess(int col, int row, char symbol = 'O', double damage = 0, double hp = 1) :
		ActiveCharacter(col, row, symbol, damage, hp) {};
	void collide(Character &other, const std::shared_ptr<Map> map) override;
	void collide(Knight &other, const std::shared_ptr<Map> map);
};

class Monster : public ActiveCharacter
{
public:
	Monster(int col, int row, char symbol = 'M', int visibility = 5, double damage = 7, double hp = 100) :
		ActiveCharacter(col, row, symbol, damage, hp), _visibility(visibility) {};
	void collide(ActiveCharacter &other, const std::shared_ptr<Map> map) override;
	void collide(Princess &other, const std::shared_ptr<Map> map);
	void collide(Health &other, const std::shared_ptr<Map> map) override;
	void collide(Mana &other, const std::shared_ptr<Map> map) override;
	void make_move_to_knight(int knight_col, int knight_row, const std::shared_ptr<Map> map) override;
	int get_visibility() const { return _visibility; }
private:
	int _visibility;
};

class Wall : public Character
{
public:
	Wall(int col, int row, char symbol = '#') : Character(col, row, symbol) {}
	bool is_transparent() override { return false; }
	void collide(Character &other, const std::shared_ptr<Map> map) override;
	void collide(Projectile &other, const std::shared_ptr<Map> map) override;
	void collide(ActiveCharacter &other, const std::shared_ptr<Map> map) override;
};

class Projectile : public ActiveCharacter
{
public:
	Projectile(int col, int row, int dir_to_col, int dir_to_row,
		char symbol = '*', double damage = 50, double hp = 1, bool is_made_turn = false)
		: ActiveCharacter(col, row, symbol, damage, hp, is_made_turn), 
		_dir_to_col(dir_to_col), _dir_to_row(dir_to_row), _cost(40) {}
	void move_to(int to_col, int to_row, const std::shared_ptr<Map> map) override;
	bool is_transparent() override { return true; }
	double cost() override { return _cost; }
	void collide(ActiveCharacter &other, const std::shared_ptr<Map> map) override;
	void collide(Character &other, const std::shared_ptr<Map> map) override;
	void collide(Princess &other, const std::shared_ptr<Map> map);
	void collide(Health &other, const std::shared_ptr<Map> map) override;
	void collide(Mana &other, const std::shared_ptr<Map> map) override;
	int get_dir_col() const override { return _dir_to_col; } 
	int get_dir_row() const override { return _dir_to_row; }
private:
	double _cost;
	int _dir_to_col, _dir_to_row;
};

class Health : public Character {
public:
	Health(int col, int row, char symbol = 'H', double damage = 0, double hp = 100) : Character(col, row, symbol, damage, hp) {}
	bool is_transparent() override { return true; }
	void collide(Character &other, const std::shared_ptr<Map> map) override;
	void collide(Projectile &other, const std::shared_ptr<Map> map) override;
	void collide(ActiveCharacter &other, const std::shared_ptr<Map> map) override;
};

class Mana : public Character {
public:
	Mana(int col, int row, char symbol = 'E', double damage = 0, double hp = 100) : Character(col, row, symbol, damage, hp) {}
	bool is_transparent() override { return true; }
	void collide(Character &other, const std::shared_ptr<Map> map) override;
	void collide(Projectile &other, const std::shared_ptr<Map> map) override;
	void collide(ActiveCharacter &other, const std::shared_ptr<Map> map) override;
};