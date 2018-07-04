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
	while (true) {
		int key = getch();
		switch (key) {
		case 'w': {
			game.move_active_characters();
			game.knight()->move_to(-1, 0, game.map());
			break;
		}
		case 's': {
			game.move_active_characters();
			game.knight()->move_to(1, 0, game.map());
			break;
		}
		case 'd': {
			game.move_active_characters();
			game.knight()->move_to(0, 1, game.map());
			break;
		}
		case 'a': {
			game.move_active_characters();
			game.knight()->move_to(0, -1, game.map());
			break;
		}
		case 'k': {
			game.shoot(1, 0);
			game.move_active_characters();
			break;
		}
		case 'i': {
			game.shoot(-1, 0);
			game.move_active_characters();
			break;
		}
		case 'j': {
			game.shoot(0, -1);
			game.move_active_characters();
			break;
		}
		case 'l': {
			game.shoot(0, 1);
			game.move_active_characters();
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
