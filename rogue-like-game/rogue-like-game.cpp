// rogue-like-game.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "curses.h"
#include <iostream>
#include <string>

int main()
{
	char f;
	initscr();
	while (true) {
		f = getch();
		clear();
		printw("dsfs");
	}
	endwin();
    return 0;
}

