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
			if (s == 'H') {
				_map_ptr->set_cell(i, j, std::make_shared<MapCell>(std::make_shared<Character>(i, j), std::make_shared<Health>(i, j)));
				continue;
			}
			if (s == 'E') {
				_map_ptr->set_cell(i, j, std::make_shared<MapCell>(std::make_shared<Character>(i, j), std::make_shared<Mana>(i, j)));
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
	if (_knight->is_dead()) {
		printw("OOOOOOOOOOOOpppsssss, U DIED");
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
		addstr((" MP: " + std::to_string(_knight->mana()) + "\n").c_str());
	}
	refresh();
}

void Game::make_turn(EventManager event_manager)
{
	event_manager.move_projectiles(*this, map());
	
	/*for (auto character : _projectiles) {
		if (!character->is_made_turn()) {
			character->move_to(character->get_dir_col(), character->get_dir_row(), map());
		}
	}*/
	move_active_characters();
	event_manager.trigger_all(*this, map());
	event_manager.spawn_projectiles(*this, map());
	for (auto i = _projectiles.begin(); i != _projectiles.end();) {
		i->get()->is_made_turn(false);
		if (i->get()->is_dead()) {
			_map_ptr->move_character(i->get()->get_col(), i->get()->get_row(), i->get()->get_col(), i->get()->get_row());
			i = _projectiles.erase(i);
		}
		else
			i++;
	}
	_knight->is_made_turn(false);
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
	if (!_knight->is_made_turn())
		_knight->move_to(_knight->get_dir_col(), _knight->get_dir_row(), _map_ptr);
	for (auto character : _active_characters) {
		if (!character->is_dead())
			character->make_move_to_knight(knight()->get_col(), knight()->get_row(), map());
	}
}

void Game::shoot(int dir_col, int dir_row)
{
	_knight->is_made_turn(true);
	auto a = std::make_shared<Projectile>(_knight->get_col(), _knight->get_row(), dir_col, dir_row);
	if (map()->is_inrange(_knight->get_col() + dir_col, _knight->get_row() + dir_row) && _knight->mana() >= a->cost()){
		EventManager::get_manager().add_projectile(a, a->get_col() + a->get_dir_col(), a->get_row() + a->get_dir_row());
		_knight->mana(-a->cost());
	}
}

std::vector<std::shared_ptr<Character>> Game::get_projectiles()
{
	return _projectiles;
}

void Game::push_to_projectiles(std::shared_ptr<Character> projectile)
{
	_projectiles.push_back(projectile);
}

std::_Vector_iterator<std::_Vector_val<std::_Simple_types<std::shared_ptr<Character>>>> Game::get_projectile_begin()
{
	return _projectiles.begin();
}

std::_Vector_iterator<std::_Vector_val<std::_Simple_types<std::shared_ptr<Character>>>> Game::get_projectile_end()
{
	return _projectiles.end();
}

std::_Vector_iterator<std::_Vector_val<std::_Simple_types<std::shared_ptr<Character>>>>
	Game::erase_projectile(std::_Vector_iterator<std::_Vector_val<std::_Simple_types<std::shared_ptr<Character>>>> index)
{
	return _projectiles.erase(index);
}