// rogue-like-game.cpp: определяет точку входа для консольного приложения.

#include "stdafx.h"
#include "Game.h"
#include "Character.h"
#include "Map.h"
#include <fstream>
#include <vector>
#include "curses.h"

class Game;

int main()
{
	std::ifstream file;
	file.open("map.txt");
	int h, w;
	file >> h >> w;
	std::vector<std::vector<std::shared_ptr<MapCell>>> level;
	level.resize(h);
	char s;
	for (int i = 0; i < h; ++i) {
		level[i].resize(w);
		for (int j = 0; j < w; ++j) {
			file >> s;
			if (i == 0 && j == 0) {
				level[i][j] = std::make_shared<MapCell>(std::make_shared<StaticCharacter>(), std::make_shared<Knight>());
				continue;
			}
			if (s == '.'){
				level[i][j] = std::make_shared<MapCell>(std::make_shared<StaticCharacter>(), std::make_shared<EmptyFloor>());
			}
		}
	}
	
	Game game(std::make_shared<Map>(level), std::make_shared<Knight>());
	std::shared_ptr<Character> knight = level[0][0]->get_character();
	game.draw();
	while (true) {
		int key = getch();
		switch (key) {
		case 119: {
			game.knight()->move_to(-1, 0);
			break;
		}
		case 115: {
			game.knight()->move_to(1, 0);
			break;
		}
		case 100: {
			game.knight()->move_to(0, 1);
			break;
		}
		case 97: {
			game.knight()->move_to(0, -1);
			break;
		}
		default: {
			continue;
		}
		}
	}
	int a = 0;
	return 0;
}

