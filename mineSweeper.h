//Filename: mineSweeper.h
//Author: Gavin Limchayseng
//Date: 10/12/17

#pragma once
#include <string>
#include <iostream>
#include <time.h>

class Minesweeper{
	public:
		Minesweeper();
		~Minesweeper();
		void initializeBoard(int diff);
		void displayBoard();
		void displayMines();
		void playMinesweeper();
		void checkMines(int r, int c);
		bool exists(int r, int c);

	private:
		char** board;
		char** cover;
		int mines;
		int size;
};