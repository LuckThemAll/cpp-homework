#include "stdafx.h"
#include "UI.h"
#include "Map.h"
#include "EventManager.h"
#include "Game.h"

	

void UI::start_game()
{
	Game game(std::make_shared<Map>(), std::make_shared<Knight>(0, 0));
	game.make_map();
	game.draw();
	//EventManager event_manager;
	while (true) {
		int key = getch();
		switch (key) {
		case 119: {
			game.knight()->move_to(-1, 0, game.map());
			break;
		}
		case 115: {
			game.knight()->move_to(1, 0, game.map());
			break;
		}
		case 100: {
			game.knight()->move_to(0, 1, game.map());
			break;
		}
		case 97: {
			game.knight()->move_to(0, -1, game.map());
			break;
		}
		default: {
			continue;
		}
		}
		game.make_turn(EventManager::get_manager());
		game.draw();
	}
}
