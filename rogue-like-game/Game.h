#pragma once

#include "Map.h"

class Game;
class Knight;

class Game {
public:
	Game(std::shared_ptr<Map> map, std::shared_ptr<Knight> knight) : _map(map), _knight(knight) {};
	std::shared_ptr<Knight> knight() { return _knight; };
	void draw();
private:
	std::shared_ptr<Knight> _knight;
	std::shared_ptr<Map> _map;
};