#pragma once

#include "Map.h"

class Game;
class Knight;
class EventManager;

class Game {
public:
	Game(std::shared_ptr<Map> map, std::shared_ptr<Knight> knight);
	std::shared_ptr<Knight> &knight() { return _knight; };
	std::shared_ptr<Map> &map() { return _map; };
	void make_map();
	void draw();
	void make_turn(EventManager event_manager);
private:
	std::shared_ptr<Knight> _knight;
	std::shared_ptr<Map> _map;
};