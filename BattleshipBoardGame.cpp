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
const unsigned char EMPTY = 0;
const unsigned char NUM_MASK = 0b0000111;
const unsigned char DIR_MASK = 0b0000001;
const unsigned char HIT_MASK = 0b1000000;

unsigned char P1Board[BOARD_HEIGHT][BOARD_WIDTH];
unsigned char P2Board[BOARD_HEIGHT][BOARD_WIDTH];


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

// Check if a cell is a ship
bool IsShip(unsigned char cell) {
	// ignore hit bit; set hit bit to 0
	cell &= ~HIT_MASK;

	return cell != EMPTY;
}

// Returns whether a ship part has been hit
bool ShipIsHit(unsigned char ship) {
	bool isHit = (ship & HIT_MASK) << 1;
	return isHit;
}

// Toggle a ship part's hit status
unsigned char ShipToggleHit(unsigned char ship) {
	return ship ^ HIT_MASK;
}

// Check if a ship can be placed at a position
bool IsLegalShipPos(unsigned char board[BOARD_HEIGHT][BOARD_WIDTH], int x, int y, unsigned char ship) {
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
bool PlaceShip(unsigned char (&board)[BOARD_HEIGHT][BOARD_WIDTH], int x, int y, unsigned char ship) {
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
void PlaceAllShips(unsigned char (&board)[BOARD_HEIGHT][BOARD_WIDTH]) {}

// Output board for user
void DisplayBoard(unsigned char board[BOARD_HEIGHT][BOARD_WIDTH]) {
	// Display column headers
	cout << "  ";
	for (int i = 0; i < BOARD_WIDTH; i++) {
		cout << i + 1 << " ";
	}
	
	cout << endl;
	
	// Display rows with row numbers and cell status
	// Iterating through rows
	for (int i = 0; i < BOARD_WIDTH; i++) { 
		// Output row header
		cout << static_cast<char>('A' + i) << ' ';

		// Iterating through columns
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			unsigned char cell = board[j][i];

			if (cell == EMPTY){
				cout << "~ ";
				continue;
			}

			// HIT_MASK is zero other than the hit bit
			// we treat this as a hit on an empty cell
			if (cell == HIT_MASK) {
				cout << "O ";
			}
			else if (ShipIsHit(cell)) {
				cout << "X ";
			}
			else {
				cout << "S ";
			}
		}
		cout << endl;
	}
}

// Check all ships for game over condition. Set winner to the winning board, or 0 if game isn't over.
bool GameOver(unsigned char board1[BOARD_HEIGHT][BOARD_WIDTH], unsigned char board2[BOARD_HEIGHT][BOARD_WIDTH], int &winner) {
	bool board1Wins = false;
	bool board2Wins = false;

	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			unsigned char cell1 = board1[i][j];
			unsigned char cell2 = board2[i][j];

			// if an unharmed ship is found, that side must not be the loser
			board1Wins = IsShip(cell1) && !ShipIsHit(cell1);
			board2Wins = IsShip(cell2) && !ShipIsHit(cell2);
		}
	}

	if (board1Wins && board2Wins) {
		// Game isn't finished since both sides have not lost
		winner = 0;
		return false;
	}

	// Game is finished; one side must have lost
	if (board1Wins) {
		winner = 1;
	}
	else if (board2Wins) {
		winner = 2;
	}

	return true;
}

// Parse the user's input into a board position
void ParsePosition(string position, int &x, int &y) {
	// Converting letter to row index and number to column index
	x = position[0] - 'A';
	y = position[1] - '1';
}

// Get the input position from the user
void GetInputPosition(int &x, int &y) {
	/*
	getline(inputStr)

	while invalid input position:
		output "Enter position: "
		getline(inputStr)

		position = ParsePosition(inputStr)

		invalid = IsHit(board[position])

		if position is invalid:
			error message

	set x ref to input position x
	set y ref to input position y
	*/
}

// Initialize game boards with empty cells
void InitializeBoard(unsigned char board[BOARD_HEIGHT][BOARD_WIDTH]){
	for (int i = 0; i < BOARD_HEIGHT; i++){
		for (int j = 0; j < BOARD_WIDTH; j++){
			board[i][j] = 0;
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

	// test DisplayBoard
	DisplayBoard(P1Board);

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


		position = GetInputPosition()

		hit = currentBoard[position] is ship
		currentMap[position] = hit

		output if a hit or miss

		output "Switch to player 2 and press enter:"
		// wait for user to press enter by get input into an unused dummy var
		// getline is probably better since it terminates at a newline
		cin >> dummy variable

		if turn == player1:
			turn = player2
		else:
			turn = player1
	*/
	
	return 0;
}