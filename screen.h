#ifndef SCREEN_H
#define SCREEN_H
#include <windows.h>
#include <iostream>

namespace screen {
//directs console cursor to specified coordinates
//
	void gotoxy(int x, int y)
	{
		COORD c = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
		return;
	}
//prints whitespace to screen, effectively clearing it
//
	void resetscreen() {

		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 12; j++) {
					std::cout << " ";
				
			}
		}
		gotoxy(0, 0);
		return;
	}
//clears larger area. Takes more time to do this though.
//
	void clearscreen() {
		gotoxy(0, 0);
		for (int i = 0; i < 60; i++) {
			for (int j = 0; j < 60; j++) {
				std::cout << " ";
			}
		}
		gotoxy(0, 0);
	}


}

#endif