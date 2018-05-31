// rogue-like-game.cpp: определяет точку входа для консольного приложения.

#include "include\curses.h"
#include "stdafx.h"
#include "Game.h"
#include "Character.h"
#include "Map.h"
#include <fstream>
#include <vector>

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
			if (s == '.'){
				level[i][j] = std::make_shared<MapCell>(std::make_shared<StaticCharacter>(), std::make_shared<EmptyFloor>());
			}
		}
	}
	return 0;
}

