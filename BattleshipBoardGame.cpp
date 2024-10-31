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
const unsigned char NUM_MASK = 0b0000111;
const unsigned char DIR_MASK = 0b0000001;
const unsigned char HIT_MASK = 0b1000000;

int P1Board[BOARD_HEIGHT][BOARD_WIDTH];
int P2Board[BOARD_HEIGHT][BOARD_WIDTH];


/*
	Return an int representing a ship or a part of a ship
		length: Ship length.
		direction: 0 for horizontal, 1 for vertical.
		i: Index of ship part, relative to the ship's position. 
		   If building a ship and not a single part of a ship, set to 0.
		   For horizontal ships, 0 indicates the first part starting at the left.
		   For vertical ships, 0 indicates the first part starting from the top
*/
unsigned char BuildShip(int length, int direction, int i) {
	/* a ship is represented by a single byte
	length (3 bits), direction (1 bit), index (3 bits), hit (1 bit)
	in total this is 8 bits, or one byte
	these bits are positioned like so: hdiiilll
	where d is direction, l is length, i is the index, and h is the hit bit */

	length &= NUM_MASK;
	i &= NUM_MASK;
	direction &= DIR_MASK;

	return length | (i << 3) | (direction << 6);
}

// Return the length of a ship
int ShipLen(unsigned char ship) {
	return ship & NUM_MASK;
}

// Return the direction of a ship. false for horizontal, true for vertical.
bool ShipDirection(unsigned char ship) {
	return (ship >> 6) & DIR_MASK;
}

// Return the index of a ship
unsigned char ShipIndex(unsigned char ship) {
	return (ship >> 3) & NUM_MASK;
}

// Set the index of a ship, and return the modified ship
unsigned char ShipSetIndex(unsigned char ship, int i) {
	i &= NUM_MASK;
	ship = (ship >> 3) & ~NUM_MASK;

	return ship | i;
}

// Returns whether a ship part has been hit
unsigned char ShipIsHit(unsigned char ship) {
	bool isHit = (ship & HIT_MASK) << 1;
	return isHit;
}

// Toggle a ship part's hit status
unsigned char ShipToggleHit(unsigned char ship) {
	return ship ^ HIT_MASK;
}

// Check if a ship can be placed at a position
bool IsLegalShipPos(int board[BOARD_HEIGHT][BOARD_WIDTH], int x, int y, unsigned char ship) {
	/*
	checkX = x
	checkY = y
	isHorizontal = ShipDirection(ship) == HORIZONTAL

	for i = 0 to ShipLen(ship) - 1:
		if isHorizontal:
			checkX = x + i;
		else:
			checkY = y + i;

		if (board[checkX][checkY] != 0):
			return false

	return true
	*/
}

// Place a ship at a location on the board, returning false if the placement fails
bool PlaceShip(int (&board)[BOARD_HEIGHT][BOARD_WIDTH], int x, int y, unsigned char ship) {
	/*
	if (!IsLegalShipPos(board, x, y, ship)):
		return false

	curX = x
	curY = y
	isHorizontal = ShipDirection(ship) == HORIZONTAL

	for i = 0 to ShipLen(ship) - 1:
		if isHorizontal:
			curX = x + i;
		else:
			curY = y + i;

		board[curX][curY] = ShipSetIndex(ship, i)

	return true
	*/
}

// Initialize a board with random ship locations
void InitializeBoard(int (&board)[BOARD_HEIGHT][BOARD_WIDTH]) {}

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

//Initialize game boards with empty cells
void InitializeBoard(int board[BOARD_HEIGHT][BOARD_WIDTH]){
	for (int i = 0; i < BOARD_HEIGHT; i++){
		for (int j = 0; j < BOARD_WIDTH; j++){
			board[i][j] = EMPTY;
		}
	}
}

int main()
{
	
	int x;
	int y;
	bool turn = true;
	string position;

	InitializeBoard(P1Board);
	InitializeBoard(P2Board);

	/*

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