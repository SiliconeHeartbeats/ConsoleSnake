#include "screen.h"
#include "snake.h"

//launches into playgame() and exits after gameover(). Puts snake out of scope, and polls player to continue or not.
//
int game() {
	int choice;
	serpens snake;
	snake.playgame();
	std::cout << "\n\n Would you like to play again? Enter any non zero number for yes, zero  or any non number for no: ";
	std::cin >> choice;
	return choice;
}


int main() {
	int cont = 1;
	int& rcont = cont;
	while (cont) {
		screen::clearscreen();
		rcont = game();
	}
	
	return 0;
}