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


// output board for user
void DisplayBoard(int board[BOARD_HEIGHT][BOARD_WIDTH]) {}

// check all ships for game over condition
bool GameOver(int board1[BOARD_HEIGHT][BOARD_WIDTH], int board2[BOARD_HEIGHT][BOARD_WIDTH]) {}

// parse the user's input into a board position
void ParsePosition(string position, int &x, int &y) {}


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