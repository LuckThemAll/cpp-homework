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
class HealCharacter;
class Health;
class Mana;

enum class Direction {LEFT, RIGHT, DOWN, UP};

class Character : public std::enable_shared_from_this<Character>
{
public:
	Character(int col, int row, std::string symbol = "C", double damage = 0, double hp = INT_MAX, bool is_made_turn = false) :
		_col(col), _row(row), _symbol(symbol), _damage(damage), _hp(hp), _is_made_turn(is_made_turn) {};

	int get_col() const { return _col; }
	int get_row() const { return _row; }
	std::string get_symbol() const { return _symbol; }
	double get_damage() const { return _damage; }
	double get_hp() const { return _hp; }
	virtual bool is_transparent() const { return true; }
	bool is_dead() const { return _hp <= 0; }
	bool is_made_turn() const { return _is_made_turn; }

	void take_damage(double damage) { _hp -= damage; }
	void self_kill() { _hp = 0; }
	void heal(double hp) { _hp += hp; }

	void is_made_turn(bool result) { _is_made_turn = result; }
	void set_pos(int col, int row) { _col = col; _row = row; }
	
	virtual void move_to(int to_col, int to_row, const std::shared_ptr<Map> map) {}
	virtual void make_move_to_knight(int knight_col, int knight_row, const std::shared_ptr<Map> map) {};

	virtual void collide(Character &other, const std::shared_ptr<Map> map);
	virtual void collide(ActiveCharacter &other, const std::shared_ptr<Map> map);
	virtual void collide(Projectile &other, const std::shared_ptr<Map> map);
	virtual void collide(EmptyFloor &other, const std::shared_ptr<Map> map);
	virtual void collide(Princess &other, const std::shared_ptr<Map> map);
	virtual void collide(HealCharacter &other, const std::shared_ptr<Map> map);
	virtual void collide(Knight &other, const std::shared_ptr<Map> map);

	virtual double cost() const { return 0; };
	
	std::shared_ptr<Character> get_ptr() { return shared_from_this(); }
protected:
	bool _is_made_turn;
private:
	std::string _symbol;
	int _col, _row;
	double _damage, _hp;
};

class EmptyFloor : public Character 
{
public:
	EmptyFloor(int col, int row, std::string symbol = " ", double damage = 0, double hp = INT_MAX) :
		Character(col, row, symbol, damage, hp) {}
	void collide(Character &other, const std::shared_ptr<Map> map) override;
	virtual void collide(ActiveCharacter &other, const std::shared_ptr<Map> map);
	virtual void collide(Projectile &other, const std::shared_ptr<Map> map) {};
};

class ActiveCharacter : public Character 
{
public:
	bool is_transparent() const override { return false; }
	void move_to(int to_col, int to_row, const std::shared_ptr<Map> map);
	void collide(ActiveCharacter &other, const std::shared_ptr<Map> map) override;
	void collide(Character &other, const std::shared_ptr<Map> map) override;
	void collide(EmptyFloor &other, const std::shared_ptr<Map> map) override;
	void collide(Princess &other, const std::shared_ptr<Map> map) override;
	void collide(Projectile &other, const std::shared_ptr<Map> map) override;
	void collide(HealCharacter &other, const std::shared_ptr<Map> map) override;
	void make_move_to_knight(int knight_col, int knight_row, const std::shared_ptr<Map> map) override {};
protected:
	ActiveCharacter(int col, int row, std::string symobol = "A", double damage = 10, double hp = 100, bool is_made_turn = false) :
		Character(col, row, symobol, damage, hp, is_made_turn) {}
};

class Knight : public ActiveCharacter
{
public:
	Knight(int col, int row, std::string symbol = "K", double damage = 10, double hp = 1000, double mana = 10000) :
		ActiveCharacter(col, row, symbol, damage, hp),  _mana(mana) {};
	void collide(ActiveCharacter &other, const std::shared_ptr<Map> map) override;
	void collide(Princess &other, const std::shared_ptr<Map> map);
	void collide(HealCharacter &other, const std::shared_ptr<Map> map);
	void collide(Health &other, const std::shared_ptr<Map> map);
	void collide(Mana &other, const std::shared_ptr<Map> map);
	double mana() const { return _mana; }
	void set_dir_col(int to_col) { _dir_col = to_col; }
	void set_dir_row(int to_row) { _dir_row = to_row; }
	void set_dir(Direction dir);

	int get_dir_col() const { return _dir_col; }
	int get_dir_row() const { return _dir_row; }
	void mana(double mana) { _mana += mana; }
private:
	int _dir_col, _dir_row;
	double _mana;
};

class Princess : public ActiveCharacter
{
public:
	Princess(int col, int row, std::string symbol = "P", double damage = 0, double hp = 1) :
		ActiveCharacter(col, row, symbol, damage, hp) {};
	void collide(Character &other, const std::shared_ptr<Map> map) override;
	void collide(Knight &other, const std::shared_ptr<Map> map);
};

class Monster : public ActiveCharacter
{
public:
	Monster(int col, int row, std::string symbol = "M", int visibility = 5, double damage = 25, double hp = 100) :
		ActiveCharacter(col, row, symbol, damage, hp), _visibility(visibility) {};
	void collide(ActiveCharacter &other, const std::shared_ptr<Map> map) override;
	void collide(Princess &other, const std::shared_ptr<Map> map);
	void collide(HealCharacter &other, const std::shared_ptr<Map> map) override;
	void make_move_to_knight(int knight_col, int knight_row, const std::shared_ptr<Map> map) override;
	int get_visibility() const { return _visibility; }
private:
	int _visibility;
};

class Wall : public Character
{
public:
	Wall(int col, int row, std::string symbol = "#") : Character(col, row, symbol) {}
	bool is_transparent() const override { return false; }
	void collide(Character &other, const std::shared_ptr<Map> map) override;
	void collide(Projectile &other, const std::shared_ptr<Map> map) override;
	void collide(ActiveCharacter &other, const std::shared_ptr<Map> map) override;
};

class Projectile : public ActiveCharacter
{
public:
	Projectile(int col, int row, int dir_col, int dir_row, double cost = 40,
		std::string symbol = "*", double damage = 50, double hp = 1, bool is_made_turn = false)
		: ActiveCharacter(col, row, symbol, damage, hp, is_made_turn), 
		_dir_col(dir_col), _dir_row(dir_row), _cost(cost) {}
	void move_to(int to_col, int to_row, const std::shared_ptr<Map> map) override;
	bool is_transparent() const override { return true; }
	double cost() const override { return _cost; }
	int get_dir_col() const { return _dir_col; }
	int get_dir_row() const { return _dir_row; }
	void collide(ActiveCharacter &other, const std::shared_ptr<Map> map) override;
	void collide(Character &other, const std::shared_ptr<Map> map) override;
	void collide(Princess &other, const std::shared_ptr<Map> map);
	void collide(HealCharacter &other, const std::shared_ptr<Map> map);
private:
	int _dir_col, _dir_row;
	double _cost;
};

class HealCharacter : public Character {
public:
	bool is_transparent() const override { return true; }
	void collide(Character &other, const std::shared_ptr<Map> map) override;
	void collide(Projectile &other, const std::shared_ptr<Map> map) override;
	void collide(ActiveCharacter &other, const std::shared_ptr<Map> map) override;
	void collide(Knight &other, const std::shared_ptr<Map> map) override;
protected:
	HealCharacter(int col, int row, std::string symbol = "+", double damage = 0, double hp = 100) : Character(col, row, symbol, damage, hp) {}
};

class Health : public HealCharacter {
public:
	Health(int col, int row, std::string symbol = "H", double damage = 0, double hp = 100) : HealCharacter(col, row, symbol, damage, hp) {}
	void collide(Knight &other, const std::shared_ptr<Map> map) override;
};

class Mana : public HealCharacter {
public:
	Mana(int col, int row, std::string symbol = "E", double damage = 0, double hp = 100) : HealCharacter(col, row, symbol, damage, hp) {}
	void collide(Knight &other, const std::shared_ptr<Map> map) override;
};