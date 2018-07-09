#include "stdafx.h"
#include "UI.h"
#include "Map.h"
#include "EventManager.h"
#include "Game.h"

	

void UI::start_game()
{
	Game game(std::make_shared<Map>(), std::make_shared<Config>());
	game.draw();
	halfdelay(1);
	const auto cfg = game.config()->json();
	while (true) {
		int key = getch();
		if (key == cfg["move_up"]) {
			game.knight()->set_dir(Direction::UP);
		}else
		if (key == cfg["move_down"]) {
			game.knight()->set_dir(Direction::DOWN);
		}else
		if (key == cfg["move_right"]) {
			game.knight()->set_dir(Direction::RIGHT);
		}else
		if (key == cfg["move_left"]) {
			game.knight()->set_dir(Direction::LEFT);
		}else
		if (key == cfg["shoot_down"]) {
			game.shoot(Direction::DOWN);
		}else
		if (key == cfg["shoot_up"]) {
			game.shoot(Direction::UP);
		}else
		if (key == cfg["shoot_left"]) {
			game.shoot(Direction::LEFT);
		}else
		if (key == cfg["shoot_right"]) {
			game.shoot(Direction::RIGHT);
		}else
		if (key == cfg["restart"]) {
			game.restart();
		}else
			game.knight()->is_made_turn(true);
		game.make_turn(EventManager::get_manager());
		game.draw();
	}
}
