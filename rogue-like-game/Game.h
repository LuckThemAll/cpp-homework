#pragma once
#include "curses.h"
#include "Map.h"

class Game;
class Knight;
class EventManager;

class Game 
{
public:
	Game(std::shared_ptr<Map> map_ptr, std::shared_ptr<Knight> knight) : _map_ptr(map_ptr), _knight(knight) {}
	std::shared_ptr<Knight> knight() { return _knight; }
	std::shared_ptr<Map> map() { return _map_ptr; }
	void make_map();
	void draw();
	void make_turn(EventManager event_manager);
	void move_active_characters();
	void shoot(int dir_col, int dir_row);
private:
	std::vector<std::shared_ptr<Character>> _active_characters;
	std::vector<std::shared_ptr<Character>> _projectiles;
	std::shared_ptr<Knight> _knight;
	std::shared_ptr<Map> _map_ptr;
};