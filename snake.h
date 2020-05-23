#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <conio.h>
#include <chrono>
#include <thread>
#include <random>
#include <numeric>

#include "board.h"

class Serpens {
//segx stores 'x coordinates' of snake segments', segy stores 'y coordinates' of snake segments. state is changed in event of gameover() and ends game loop
//move stores the input that directs the snake head, with every segment behind it occupying the space behind the segment ahead of it, and storing
//their position into segx and segy. snakeLength determines how large the segx and segy vectors are, and as such how many segments follow the head.
//this in turn, as expected, determines the snake's size. headx and heady store coordinates of, and fruitx/fruity follow suit with the fruit.
	Board SnakeBoard;					
	
	std::vector<int> segx = {7,6,5};
	std::vector<int> segy = {7,7,7};
	int state = 1;
	char move = 'w';

	int snakeLength = 3;
	int heady = 7;
	int headx = 7;
	int fruitx;
	int fruity;
	
public:

//reads input direct from keyboard and ignores all chars that aren't w,s,a,d. 
//

	void getinput() {
		char entry = _getch();
		switch (entry) {

		case 'w':
			move = entry;
			break;
		case 'a':
			move = entry;
			break;
		case 's':
			move = entry;
			break;
		case 'd':
			move = entry;
			break;
		default:
			return;
			break;
		}

		
		
		return;
	}
//reads input char, and checks if 1) that direction would lead the snake head into a wall and 2) if that direction would
//direct the snakehead into a segment of the snake. If either of these are true, a gameover is triggered. otherwise, it moves
//the head in that direction, with every segment behind it replacing the space that was once occupied by the segment ahead of it.
//segment positions are stored with their coordinates in the segx and segy vectors. The head feeds its position into this vector and
//every segment behind it reads from the vectors in an iterated fashion, with the last segment printing whitespace into the position
//marked by the last elements of segx and segy.
	void slither() {
		
				
				switch (move) {
				
				case 'w':
					if (SnakeBoard.gameboard[heady-1][headx] == 'o') {			//is snake head moving into snake body?
						gameover();												//gameover.
						break;
					}
					if (heady != 1) {											//is snake heading into wall? (see board.h for reference)
						SnakeBoard.gameboard[(heady - 1)][headx] = 'O';			//if not, move
						heady = heady - 1;
						segy.push_back(heady);
						segx.push_back(headx);
						break;
					}
					else {														//if so, gameover
						gameover();
						break;
					}
				
				case 's':
					if (SnakeBoard.gameboard[heady + 1][headx] == 'o') {
						gameover();
						break;
					}
					if (heady != 10) {
						SnakeBoard.gameboard[(heady + 1)][headx] = 'O';
						heady = heady + 1;
						segy.push_back(heady);
						segx.push_back(headx);
						break;
					}
					else {
						gameover();
						break;
					}
				case 'a':
					if (SnakeBoard.gameboard[heady][headx - 1] == 'o') {
						gameover();
						break;
					}
					if (headx != 1) {
						SnakeBoard.gameboard[heady][(headx - 1)] = 'O';
						headx = headx - 1;
						segy.push_back(heady);
						segx.push_back(headx);
						break;
					}
					else {
						gameover();
						break;
					}
				case 'd':
					if (SnakeBoard.gameboard[heady][headx + 1] == 'o') {
						gameover();
						break;
					}
					if (headx != 10) {
						SnakeBoard.gameboard[heady][(headx + 1)] = 'O';
						headx = headx + 1;
						segy.push_back(heady);
						segx.push_back(headx);
						break;
					}
					else {
						gameover();
						break;
					}
				default:
					
					break;
				}
			
				for (int i = 0; i < snakeLength; i ++){					//detects if segment is last segment, 
																		//and prints whitespace in 'behind' it
				if(i != (snakeLength - 1)) {

					SnakeBoard.gameboard[(segy.at(i))][(segx.at(i))] = 'o';
					segy.push_back((segy.at(i)));
					segx.push_back((segx.at(i)));


			}
			
				else {
				
					SnakeBoard.gameboard[(segy.at(i))][(segx.at(i))] = ' ';

			}
		}

		SnakeBoard.printboard();										//prints updated game board 
		screen::resetscreen();											//clears screen for further moves
		segy.erase(segy.begin(), segy.begin() + snakeLength);			//clears previous turns moves and 'segment positions' from vectors.
		segx.erase(segx.begin(), segx.begin() + snakeLength);			//bigger snakeLength value means bigger buffer meaning more segments can be stored
		return;
	}
//randomly generates fruit coordinates bounded so that it cannot spawn into walls, and stores the coordinates into fruity/fruitx.
//prints an 'F' to the appropriate spot on the board.
	void spawnfruit() {
		
			std::random_device rd;
			std::mt19937 eng(rd());
			std::uniform_int_distribution<>	distr(1, 9);
			fruitx = distr(eng);
			fruity = distr(eng);
			snakeboard.gameboard[fruity][fruitx] = 'F';
			return;
	}
//checks for fruit at head location. increases snake's length and spawns another fruit if the if tests positive.
//
//biggest issue with fruit is board size, and the fact fruit can spawn where a segment is and thus be replaced by whitespace
//and be invisible. a bigger board and consequently a large distribution range would fix this, or multiple fruit spawns. But
//this still works as a simple exercise in the console.
	void checkfruit() {

		if ((headx == fruitx) && (heady == fruity)) {

			getfruit();
			spawnfruit();
		}
		return;
	}
//increases the segment buffer and spawns a segment behind the last segment on the snake. 
//
	void getfruit() {
		
		segx.push_back(segx.at(segx.size() - 1) + 1);
		segy.push_back(segy.at(segy.size() - 1));
		snakeLength++;
		return;
	}
//game over. this whole part is a mess, but it ends the while loop and exits back to main through the if statement.
//
	void gameover() {
		
		state = 0;
		return;
	}
	
	void playgame() {

		spawnfruit();
		while (state) {
			while (!_kbhit()) {
				slither();
				checkfruit();
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				if (state == 0) {
					screen::clearscreen();
					std::cout << "GAMEOVER";
					return;
				}
			}
			getinput();
			slither();
			checkfruit();
			if (state == 0) {
				screen::clearscreen();
				std::cout << "GAMEOVER";
				return;
			}
		}
		
		return;
	}
};



#endif
