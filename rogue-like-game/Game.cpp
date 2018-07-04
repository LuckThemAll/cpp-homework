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
	_map_ptr->get_map()->resize(height);
	auto a = _map_ptr;
	for (int i = 0; i < height; ++i) {
		_map_ptr->get_col(i).resize(width);
		for (int j = 0; j < width; ++j) {
			file >> s;
			if (i == 0 && j == 0) {
				_map_ptr->set_cell(i, j, std::make_shared<MapCell>(std::make_shared<Character>(i, j), knight()));
				continue;
			}
			if (s == '#') {
				_map_ptr->set_cell(i, j, std::make_shared<MapCell>(std::make_shared<Character>(i, j), std::make_shared<Wall>(i, j)));
				continue;
			}
			if (s == '.') {
				_map_ptr->set_cell(i, j, std::make_shared<MapCell>(std::make_shared<Character>(i, j), std::make_shared<EmptyFloor>(i, j)));
				continue;
			}
			if (s == 'M') {
				_map_ptr->set_cell(i, j, std::make_shared<MapCell>(std::make_shared<Character>(i, j), std::make_shared<Monster>(i, j)));
				auto a = _map_ptr->get_cell(i, j)->get_character();
				_active_characters.push_back( a);
				continue;
			}
			if (s == 'O') {
				_map_ptr->set_cell(i, j, std::make_shared<MapCell>(std::make_shared<Character>(i, j), std::make_shared<Princess>(i, j)));
				continue;
			}
		}
	}
}

void Game::draw() {
	initscr();
	noecho();
	raw();
	clear();
	if (_knight->is_winner()) {
		printw("woowowowowowoow, u are WIIIIINENNENENNEER");
	}
	else{
		for (int i = 0; i < _map_ptr->get_cols_num(); i++) {
			for (int j = 0; j < _map_ptr->get_rows_num(); j++) {
				char k[2];
				k[0] = _map_ptr->get_cell(i, j)->get_character()->get_symbol();
				k[1] = '\0';
				printw(k);
			}
			printw("\n");
		}
		addstr((" HP: " + std::to_string(_knight->get_hp()) + "\n").c_str());
	}
	refresh();
}

void Game::make_turn(EventManager event_manager)
{
	event_manager.trigger_all(_map_ptr);
	for (auto i = _active_characters.begin(); i != _active_characters.end();) {
		if (i->get()->is_dead()) {
			_map_ptr->move_character(i->get()->get_col(), i->get()->get_row(), i->get()->get_col(), i->get()->get_row());
			i = _active_characters.erase(i);
		}
		else
			i++;
	}

}

void Game::move_active_characters()
{
	for (auto character : _projectiles) {
		character->move_to(character->get_dir_col(), character->get_dir_row(), map());
	}
	//make_disitioon 
	for (auto character : _active_characters) {
		character->make_move_to_knight(knight()->get_col(), knight()->get_row(), map());
	}
}

void Game::add_projectile(int col, int row, int dir_col, int dir_row)
{
	auto a = std::make_shared<Projectile>(col, row, dir_col, dir_row);
	_projectiles.push_back(a);
	a->move_to(col, row, map());
}
