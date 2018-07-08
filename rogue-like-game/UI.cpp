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
			game.knight()->set_dir(Direction::UP);
			break;
		}
		case 's': {
			game.knight()->set_dir(Direction::DOWN);
			break;
		}
		case 'd': {
			game.knight()->set_dir(Direction::RIGHT);
			break;
		}
		case 'a': {
			game.knight()->set_dir(Direction::LEFT);
			break;
		}
		case 'k': {
			game.shoot(Direction::DOWN);
			break;
		}
		case 'i': {
			game.shoot(Direction::UP);
			break;
		}
		case 'j': {
			game.shoot(Direction::LEFT);
			break;
		}
		case 'l': {
			game.shoot(Direction::RIGHT);
			break;
		}
		default: {
			game.knight()->is_made_turn(true);
			break;
		}
		}
		game.make_turn(EventManager::get_manager());
		game.draw();
	}
}
