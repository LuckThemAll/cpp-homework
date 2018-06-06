#include "stdafx.h"
#include "Game.h"
#include <string>
#include "include\curses.h"

void Game::draw() {
	initscr();
	noecho();
	raw();
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

