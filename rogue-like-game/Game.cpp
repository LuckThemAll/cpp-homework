#include "stdafx.h"
#include "Game.h"
#include <string>
#include <fstream>


void Game::make_map()
{
	std::ifstream file;
	file.open("map.txt");
	int height, width;
	file >> height >> width;
	char s;
	_map->get_map()->resize(height);
	auto a = _map;
	for (int i = 0; i < height; ++i) {
		_map->get_col(i).resize(width);
		for (int j = 0; j < width; ++j) {
			file >> s;
			if (i == 0 && j == 0) {
				_map->set_cell(i, j, std::make_shared<MapCell>(std::make_shared<Character>(i, j, '.'), knight()));
				continue;
			}
			if (i == 2 && j == 2) {
				_map->set_cell(i, j, std::make_shared<MapCell>(std::make_shared<Character>(i, j, '.'), std::make_shared<Wall>(i, j)));
				continue;
			}
			if (s == '.') {
				_map->set_cell(i, j, std::make_shared<MapCell>(std::make_shared<Character>(i, j, '.'), std::make_shared<EmptyFloor>(i, j, '0')));
			}
		}
	}
	int sada = 0; //debug
}

void Game::draw() {
	initscr();
	noecho();
	raw();
	clear();
	for (int i = 0; i < _map->get_cols_num(); i++) {
		for (int j = 0; j < _map->get_rows_num(); j++) {
			char k[2];
			k[0] = _map->get_cell(i, j)->get_character()->get_symbol();
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


