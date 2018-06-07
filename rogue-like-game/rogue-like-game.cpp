// rogue-like-game.cpp: определяет точку входа для консольного приложения.

#include "stdafx.h"
#include "Game.h"
#include "Character.h"
#include "Map.h"
#include <fstream>
#include <vector>
#include "curses.h"

class Game;

int main()
{
	std::vector<std::vector<std::shared_ptr<MapCell>>> level;
	Game game(std::make_shared<Map>(level), std::make_shared<Knight>(0, 0));
	game.make_map();
	game.draw();
	EventManager event_manager;
	while (true) {
		int key = getch();
		switch (key) {
		case 119: {
			game.knight()->move_to(game.map(), -1, 0, event_manager);
			break;
		}
		case 115: {
			game.knight()->move_to(game.map(), 1, 0, event_manager);
			break;
		}
		case 100: {
			game.knight()->move_to(game.map(), 0, 1, event_manager);
			break;
		}
		case 97: {
			game.knight()->move_to(game.map(), 0, -1, event_manager);
			break;
		}
		default: {
			continue;
		}
		}
		game.make_turn(event_manager);
		game.draw();
	}
	int a = 0;
	return 0;
}

