#include "stdafx.h"
#include "Game.h"
#include <string>
#include <fstream>

Game::Game(std::shared_ptr<Map> map_ptr, std::shared_ptr<Config> conf)
{
	_win = false;
	_loose = false;
	_map_ptr = map_ptr;
	_config = conf;
	const auto cfg = config()->json();
	_knight = std::make_shared<Knight>(0, 0, cfg["Knight"]["symbol"],
		cfg["Knight"]["damage"], cfg["Knight"]["hp"], cfg["Knight"]["mana"]);
	make_map();

}

bool Game::is_win(std::shared_ptr<Character> princess)
{
	return princess->get_col() == _knight->get_col() && princess->get_row() == _knight->get_row();
}

void Game::make_map()
{
	std::ifstream file;
	file.open("map.txt");
	const auto cfg = config()->json();
	int height = cfg["height"], width = cfg["width"];
	std::string s;
	_map_ptr->get_map()->resize(height);
	auto a = _map_ptr;
	auto symbol_str = config()->get_symbol_str();
	auto damage_str = config()->get_damage_str();
	auto hp_str = config()->get_hp_str();
	for (int i = 0; i < height; ++i) {
		_map_ptr->get_col(i).resize(width);
		file >> s;
		for (int j = 0; j < width; ++j) {
			char c = s[j];
			auto mem = cfg["EmptyFloor"][symbol_str].dump()[1];
			if (i == 0 && j == 0) {
				_map_ptr->set_cell(i, j, std::make_shared<MapCell>(std::make_shared<EmptyFloor>(i, j), knight()));
				continue;
			}
			if (c == cfg["Wall"][symbol_str].dump()[1]) {
				_map_ptr->set_cell(i, j, std::make_shared<MapCell>(std::make_shared<EmptyFloor>(i, j), std::make_shared<Wall>(i, j)));
				continue;
			}
			if (c == cfg["EmptyFloor"]["symbol_for_parse"].dump()[1]) {
				_map_ptr->set_cell(i, j, std::make_shared<MapCell>(std::make_shared<EmptyFloor>(i, j),
					std::make_shared<EmptyFloor>(i, j, cfg["EmptyFloor"][symbol_str])));
				continue;
			}
			if (c == cfg["Monster"][symbol_str].dump()[1]) {
				_map_ptr->set_cell(i, j, std::make_shared<MapCell>(std::make_shared<EmptyFloor>(i, j),
					std::make_shared<Monster>(i, j, cfg["Monster"][symbol_str], cfg["Monster"]["visibility"], 
						cfg["Monster"][damage_str], cfg["Monster"][hp_str])));
				auto a = _map_ptr->get_cell(i, j)->get_character();
				_active_characters.push_back( a);
				continue;
			}
			if (c == cfg["Princess"][symbol_str].dump()[1]) {
				_map_ptr->set_cell(i, j, std::make_shared<MapCell>(std::make_shared<EmptyFloor>(i, j), 
					std::make_shared<Princess>(i, j, cfg["Princess"][symbol_str])));
				set_princess(_map_ptr->get_cell(i, j)->get_character());
				continue;
			}
			if (c == cfg["Health"][symbol_str].dump()[1]) {
				_map_ptr->set_cell(i, j, std::make_shared<MapCell>(std::make_shared<EmptyFloor>(i, j), 
					std::make_shared<Health>(i, j, cfg["Health"][symbol_str], cfg["Character"][damage_str], cfg["Health"][hp_str])));
				continue;
			}
			if (c == cfg["Mana"][symbol_str].dump()[1]) {
				_map_ptr->set_cell(i, j, std::make_shared<MapCell>(std::make_shared<EmptyFloor>(i, j), 
					std::make_shared<Mana>(i, j, cfg["Mana"][symbol_str], cfg["Character"][damage_str], cfg["Mana"][hp_str])));
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
	if (!_win && !_loose){
		if (is_win(_princess)) {
			set_win(true);
			printw("woowowowowowoow, u are WIIIIINENNENENNEER\n press \"r\" ro restert");
		}
		else if (_knight->is_dead()) {
			set_loose(true);
			printw("OOOOOOOOOOOOpppsssss, U DIED/n press \"r\" ro restert");
		}else{
			for (int i = 0; i < _map_ptr->get_cols_num(); i++) {
				for (int j = 0; j < _map_ptr->get_rows_num(); j++) {
					char k[2];
					k[0] = _map_ptr->get_cell(i, j)->get_character()->get_symbol()[0];
					k[1] = '\0';
					printw(k);
				}
				printw("|\n");
			}
			for (int i = 0; i < 20; i++) {
				printw("_");
			}
			printw("\n");
			addstr((" HP: " + std::to_string(_knight->get_hp()) + "\n").c_str());
			addstr((" MP: " + std::to_string(_knight->mana()) + "\n").c_str());
		}
	}
	else
		if (_win) {
			printw("woowowowowowoow, u are WIIIIINENNENENNEER \n press \"r\" to restart");
		}
		else{
			printw("OOOOOOOOOOOOpppsssss, U DIED \n press \"r\" to restart");
		}	
	refresh();
}

void Game::make_turn(EventManager event_manager)
{
	event_manager.move_projectiles(*this, map());
	
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

void Game::shoot(Direction dir)
{
	_knight->is_made_turn(true);
	int dir_col, dir_row;
	switch (dir) {
	case Direction::UP:
		dir_col = -1;
		dir_row = 0;
		break;
	case Direction::DOWN:
		dir_col = 1;
		dir_row = 0;
		break;
	case Direction::RIGHT:
		dir_col = 0;
		dir_row = 1;
		break;
	case Direction::LEFT:
		dir_col = 0;
		dir_row = -1;
		break;
	}
	auto a = std::make_shared<Projectile>(_knight->get_col(), _knight->get_row(), dir_col, dir_row);
	if (map()->is_inrange(_knight->get_col() + dir_col, _knight->get_row() + dir_row) && _knight->mana() >= a->cost()){
		EventManager::get_manager().add_projectile(a, a->get_col() + a->get_dir_col(), a->get_row() + a->get_dir_row());
		_knight->mana(-a->cost());
	}
}

void Game::set_princess(std::shared_ptr<Character> princess)
{
	_princess = princess;
}

void Game::restart()
{
	_projectiles.clear();
	_active_characters.clear();
	_map_ptr->clear_map();
	set_loose(false);
	set_win(false);

	const auto cfg = config()->json();
	_knight = std::make_shared<Knight>(0, 0, cfg["Knight"]["symbol"],
		cfg["Knight"]["damage"], cfg["Knight"]["hp"], cfg["Knight"]["mana"]);
	make_map();
}

std::vector<std::shared_ptr<Projectile>> Game::get_projectiles()
{
	return _projectiles;
}

void Game::push_to_projectiles(std::shared_ptr<Projectile> projectile)
{
	_projectiles.push_back(projectile);
}

std::_Vector_iterator<std::_Vector_val<std::_Simple_types<std::shared_ptr<Projectile>>>> Game::get_projectile_begin()
{
	return _projectiles.begin();
}

std::_Vector_iterator<std::_Vector_val<std::_Simple_types<std::shared_ptr<Projectile>>>> Game::get_projectile_end()
{
	return _projectiles.end();
}

std::_Vector_iterator<std::_Vector_val<std::_Simple_types<std::shared_ptr<Projectile>>>>
	Game::erase_projectile(std::_Vector_iterator<std::_Vector_val<std::_Simple_types<std::shared_ptr<Projectile>>>> index)
{
	return _projectiles.erase(index);
}