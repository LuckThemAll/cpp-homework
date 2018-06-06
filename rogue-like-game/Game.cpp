#include "stdafx.h"
#include "Game.h"
#include <string>
#include "include\curses.h"

Game::Game(std::shared_ptr<Map> map, std::shared_ptr<Knight> knight)
{
	_map = map; 
	_knight = knight;
	_map->get_cell(0, 0)->set_character(knight);
}

void Game::draw() {
	initscr();
	noecho();
	raw();
	clear();
	for (int i = 0; i < _map->get_cols_num(); i++) {
		for (int j = 0; j < _map->get_rows_num(); j++) {
			char k[2];
			k[0] = _map->get_cell(i, j)->get_character()->get_sign();
			k[1] = '\0';
			printw(k);
		}
		printw("\n");
	}
	refresh();
	
}

void Game::make_turn(EventManager event_manager)
{
	event_manager.trigger_all(_map);
}


