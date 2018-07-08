#pragma once
#include "curses.h"
#include "Map.h"

class Game;
class Knight;
class EventManager;
class Map;
class Character;
class Projectile;

class Game 
{
public:
	Game(std::shared_ptr<Map> map_ptr, std::shared_ptr<Knight> knight) : _map_ptr(map_ptr), _knight(knight) {}
	std::shared_ptr<Knight> knight() { return _knight; }
	std::shared_ptr<Map> map() { return _map_ptr; }
	bool is_win(std::shared_ptr<Character> princess);
	void make_map();
	void draw();
	void make_turn(EventManager event_manager);
	void move_active_characters();
	void shoot(int dir_col, int dir_row);
	void set_princess(std::shared_ptr<Character> princess);
	std::vector<std::shared_ptr<Projectile>> get_projectiles();
	void push_to_projectiles(std::shared_ptr<Projectile> projectile);
	std::_Vector_iterator<std::_Vector_val<std::_Simple_types<std::shared_ptr<Projectile>>>> get_projectile_begin();
	std::_Vector_iterator<std::_Vector_val<std::_Simple_types<std::shared_ptr<Projectile>>>> get_projectile_end();
	std::_Vector_iterator<std::_Vector_val<std::_Simple_types<std::shared_ptr<Projectile>>>>
		erase_projectile(std::_Vector_iterator<std::_Vector_val<std::_Simple_types<std::shared_ptr<Projectile>>>> index);
private:
	std::vector<std::shared_ptr<Projectile>> _projectiles;
	std::vector<std::shared_ptr<Character>> _active_characters;
	std::shared_ptr<Knight> _knight;
	std::shared_ptr<Character> _princess;
	std::shared_ptr<Map> _map_ptr;
};