//Filename: main.cpp
//Author: Gavin Limchayseng
//Date: 10/12/17

#include <time.h>
#include <string>
#include <iostream>
#include "mineSweeper.h"

using namespace std;

int main() {
	
	cout << "WELCOME TO MINESWEEPER!" << endl << endl;
	cout << "Instructions:" << endl;
	cout << "1. Clear all the spaces and Flag all the mines to Win" << endl;
	cout << "2. Use 'd' to dig, 'f' to Flag, 'u' to Unflag" << endl;
	cout << "3. Digging a bomb means GAME OVER" << endl;

	//Loop used to play infinitely
	bool playAgain = true;
	while (playAgain) {

		Minesweeper game;
		game.playMinesweeper();

		char input = NULL;
		bool validInput = false;
		while (!validInput) {
			cout << "Would you like to play again (y/n): ";
			cin >> input;
			if (input == 'n') {
				cout << "See you later!" << endl;
				playAgain = false;
				validInput = true;
			}
			if (input == 'y') {
				validInput = true;
			}
			else {
				cout << "Invalid Input, try again" << endl;
			}
		}
	}
}





