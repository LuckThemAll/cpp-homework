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
			game.knight()->set_dir(-1, 0);
			break;
		}
		case 's': {
			game.knight()->set_dir(1, 0);
			break;
		}
		case 'd': {
			game.knight()->set_dir(0, 1);
			break;
		}
		case 'a': {
			game.knight()->set_dir(0, -1);
			break;
		}
		case 'k': {
			game.shoot(1, 0);
			break;
		}
		case 'i': {
			game.shoot(-1, 0);
			break;
		}
		case 'j': {
			game.shoot(0, -1);
			break;
		}
		case 'l': {
			game.shoot(0, 1);
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
