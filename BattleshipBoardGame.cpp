/****************************************************************
File: BattleShipBoardGame
Description:An implementation of the classic game Battleship

Authors: Christian Alexander, Alexander Newman
Class: CSCI-110-71
Date: 10/23/2024

I hereby certify that this program is entirely my own work.
*****************************************************************/

#include <iostream>

using namespace std;


const int BOARD_HEIGHT = 10;
const int BOARD_WIDTH = 10;
const char SHIP = 'S';
const char HIT = 'X';
const char MISS = 'O';
const char EMPTY = '~';

int P1Board[BOARD_HEIGHT][BOARD_WIDTH];
int P2Board[BOARD_HEIGHT][BOARD_WIDTH];


// Output board for user
void DisplayBoard(int board[BOARD_HEIGHT][BOARD_WIDTH]) {
	// Display column headers
	cout << " ";
	for (int i = 0; i < BOARD_WIDTH; i++) {
		cout << i << " ";
	
	cout << endl;
	
	// Display rows with row numbers and cell status
	for (int j = 0; j < BOARD_HEIGHT; j++) {
		if (board[i][j] == EMPTY){
			cout << "~";
		}
		else if (board[i][j] == SHIP){
			cout << "S ";
		}
		else if (board[i][j] == HIT){
			cout << "X ";
		}
		else if (board[i][j] == MISS){
			cout << "O ";
		}
		cout << endl;
	}
}
}

// Check all ships for game over condition
bool GameOver(int board1[BOARD_HEIGHT][BOARD_WIDTH], int board2[BOARD_HEIGHT][BOARD_WIDTH]) {
	// Checking if all ships on either board are sunk
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			if (board1[i][j] == SHIP || board2[i][j] == SHIP) {
				return false;
			}
		}
	}
	return true;
}

// Parse the user's input into a board position
void ParsePosition(string position, int &x, int &y) {
	// Converting letter to row index and number to column index
	x = position[0] - 'A';
	y = position[1] - '1';
}


int main()
{
	/*
	InitializeBoard(&P1Board)
	InitializeBoard(&P2Board)

	array P1Map
	array P2Map

	while not GameOver(P1Board, P2Board):
		if turn == player1:
			currentBoard = &P1Board
			currentMap = &P1Map
		else:
			currentBoard = &P2Board
			currentMap = &P2Map

		DisplayBoard(currentBoard)


		while invalid input position:
			output "Enter position: "
			getline()

			invalid = currentBoard[position] != 0 (position has already been fired at)

			if position is invalid:
				error message

		hit = currentBoard[position] is ship
		currentMap[position] = hit

		output if a hit or miss

		output "Switch to player 2 and press enter:"
		cin >> dummy variable

		if turn == player1:
			turn = player2
		else:
			turn = player1
	*/
	
	return 0;
}