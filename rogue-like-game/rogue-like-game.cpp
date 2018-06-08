#include "UI.h"
#include "stdafx.h"
#include "UI.h"
#include "Game.h"
#include "curses.h"

class Game;
class EventManager;


int main()
{

	Game game(std::make_shared<Map>(), std::make_shared<Knight>(0, 0));
	game.make_map();
	game.draw();
	EventManager event_manager;
	while (true) {
		int key = getch();
		switch (key) {
		case 119: {
			game.knight()->move_to(-1, 0, event_manager);
			break;
		}
		case 115: {
			game.knight()->move_to(1, 0, event_manager);
			break;
		}
		case 100: {
			game.knight()->move_to(0, 1, event_manager);
			break;
		}
		case 97: {
			game.knight()->move_to(0, -1, event_manager);
			break;
		}
		default: {
			continue;
		}
		}
		game.make_turn(event_manager);
		game.draw();
	}
	return 0;
}

