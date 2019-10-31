//Filename: mineSweeper.cpp
//Author: Gavin Limchayseng
//Date: 10/12/17

#include "mineSweeper.h"

using namespace std;

Minesweeper::Minesweeper() {

}

Minesweeper::~Minesweeper() {
	delete[] board;
	delete[] cover;
}

void Minesweeper::initializeBoard(int diff) {
	size = 0;
	mines = 0;
	if (diff == 0) {
		size = 9;
		mines = 10;
	}
	//Difficuly Optional
	/*
	else if (diff == 1) {
		size = 16;
		mines = 40;
	}
	else if (diff == 2) {
		size = 24;
		mines = 99;
	}
	*/

	//clearing the boards
	board = new char*[size];
	cover = new char*[size];
	for (int i = 0; i < size; i++) {
		board[i] = new char[size];
		cover[i] = new char[size];
		 
		for (int j = 0; j < size; j++) {
			board[i][j] = cover[i][j] = '-';
		}
	}

	//loading board with mines
	srand(time(NULL));
	int randomX;
	int randomY;
	for (int i = 0; i < mines;) {
		randomX = rand() % size;
		randomY = rand() % size;
		if (board[randomX][randomY] == '-') {
			board[randomX][randomY] = '*';
			i++;
		}
	}
}

//displays board
void Minesweeper::displayBoard() {
	cout << endl << "  ";
	for (int i = 0; i < size; i++) {
		cout << i << " ";
	}
	cout << endl;
	for (int i = 0; i < size; i++) {
		cout << i << " ";
		for (int j = 0; j < size; j++) {
			cout << cover[i][j] << " ";
		}
		cout << endl;
	}
}

//Function tests if mines are placed properly
void Minesweeper::displayMines() {
	cout << endl << "  ";
	for (int i = 0; i < size; i++) {
		cout << i << " ";
	}
	cout << endl;
	for (int i = 0; i < size; i++) {
		cout << i << " ";
		for (int j = 0; j < size; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

//plays game
void Minesweeper::playMinesweeper() {
	/*
	bool valid = false;
	int tempInput;
	while (!valid) {
		tempInput = -1;
		cout << "Please input a Difficulty:" << endl;
		cout << "0. Easy (9x9 board, 10 mines)" << endl;
		cout << "1. Medium (16x16 board, 40 mines)" << endl;
		cout << "2. hard (24x24 board, 99 mines)" << endl;
		cin >> tempInput;
		if (tempInput >= 0 && tempInput <= 2) {
			valid = true;
		}
		else {
			cout << "Invalid Difficulty level, Try again" << endl;
			cin.clear();
		}
	}
	*/
	int input = 0;
	bool gameOver = false;
	bool victory = false;
	bool clearBoard = false;
	bool firstMove = true;
	initializeBoard(input);

	while ((gameOver == false) && (victory == false)) {
		
		displayBoard();
		char move = NULL;
		int row = -1;
		int col = -1;
		
		cout << "Enter your Move, Row, Column (use spaces to seperate): ";
		cin >> move;
		cin >> row;
		cin	>> col; 
		cout << endl;

		if (!exists(row, col) || cin.fail()) {
			cout << "Coordinate out of bounds, Try again :(" << endl;
			cin.clear();
			cin.ignore(10, '\n');
		}
		else if (move != 'd' && move != 'f' && move != 'u') {
			cout << "Invalid command, Try again :(" << endl;
			cin.clear();
		}
		else if (move == 'd') {
			if (firstMove) {
				if (board[row][col] == '*') {
					board[row][col] = '-';
					for (int i = 0; i < 1;) {
						srand(time(NULL));
						int randomX;
						int randomY;
						randomX = rand() % size;
						randomY = rand() % size;
						if (board[randomX][randomY] == '-' && (randomX != row && randomY != col)) {
							board[randomX][randomY] = '*';
							i++;
						}
					}
				}
				checkMines(row, col);
				firstMove = false;
			}
			else if (board[row][col] == '-') {
				checkMines(row, col);
			}
			else
				gameOver = true;
		}
		else if (move == 'f')
			cover[row][col] = 'F';
		else if (move == 'u') {
			if (cover[row][col] == 'F')
				cover[row][col] = '-';
		}
		
		//checks to see if every space has been dug or flagged correctly
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (cover[i][j] == '-')
					clearBoard = false;
				//check for false flag
				if (cover[i][j] == 'F' && board[i][j] != '*')
					clearBoard = false;
			}
		}
		if (clearBoard)
			victory = true;
		
	}	
	if (gameOver) {
		cout << endl << "GAME OVER!" << endl;
		cout << endl << "  ";
		for (int i = 0; i < size; i++) {
			cout << i << " ";
		}
		cout << endl;
		for (int i = 0; i < size; i++) {
			cout << i << " ";
			for (int j = 0; j < size; j++) {
				if (board[i][j] == '*')
					cout << '*' << " ";
				else
					cout << cover[i][j] << " ";
			}
			cout << endl;
		}
	}
	if (victory)
		cout << endl << "CONGRATULATIONS!!!" << endl;
	
}

//checks each space, speads if no adjacent mine
void Minesweeper::checkMines(int r, int c) {
	int count = 48;
	
	if (cover[r][c] != '-' || board[r][c] == '*')
		return;

	//Check Top-Left
	if (exists(r - 1, c - 1)) {
		if(board[r-1][c-1] == '*')
			count++;
	}

	//Check Top
	if (exists(r - 1, c)) {
		if (board[r-1][c] == '*')
			count++;
	}

	//Check Top-Right
	if (exists(r - 1, c + 1)) {
		if (board[r-1][c+1] == '*')
			count++;
	}
	
	//Check Left
	if (exists(r, c - 1)) {
		if (board[r][c-1] == '*')
			count++;
	}

	//Check Right
	if (exists(r, c + 1)) {
		if (board[r][c+1] == '*')
			count++;
	}

	//Check Bottom-Left
	if (exists(r + 1, c - 1)) {
		if (board[r+1][c-1] == '*')
			count++;
	}

	//Check Bottom
	if (exists(r + 1, c)) {
		if (board[r+1][c] == '*')
			count++;
	}

	//Check Bottom-Right
	if (exists(r + 1, c + 1)) {
		if (board[r+1][c+1] == '*')
			count++;
	}

	if (count == 48) {
		cover[r][c] = ' ';
		//Check Top-Right
		if (exists(r - 1, c - 1)) {
			checkMines(r - 1, c - 1);
		}

		//Check Top
		if (exists(r - 1, c)) {
			checkMines(r - 1, c);
		}

		//Check Top-Right
		if (exists(r - 1, c + 1)) {
			checkMines(r - 1, c + 1);
		}

		//Check Left
		if (exists(r, c - 1)) {
			checkMines(r, c - 1);
		}

		//Check Right
		if (exists(r, c + 1)) {
			checkMines(r, c + 1);
		}

		//Check Bottom-Left
		if (exists(r + 1, c - 1)) {
			checkMines(r + 1, c - 1);
		}

		//Check Bottom
		if (exists(r + 1, c)) {
			checkMines(r + 1, c);
		}

		//Check Bottom-Right
		if (exists(r + 1, c + 1)) {
			checkMines(r + 1, c - 1);
		}
	}
	else {
		cover[r][c] = count;
	}
}

//checks to see if the spot exists
bool Minesweeper::exists(int r, int c) {
	if (r < 0 || c < 0 || r >= size || c >= size)
		return false;
	else
		return true;
}