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


// TODO: board is square, so width/height can be combined into one BOARD_SIZE constant
const int BOARD_HEIGHT = 10;
const int BOARD_WIDTH = 10;
const int NUM_SHIP_PARTS = 5 + 4 + 4 + 3 + 2;	// length of all five ships
const char SHIP = 'S';
const char HIT = 'X';
const char MISS = 'O';
const char EMPTY = '~';

char P1Board[BOARD_HEIGHT][BOARD_WIDTH];
char P2Board[BOARD_HEIGHT][BOARD_WIDTH];

int P1RemainingShipCells = NUM_SHIP_PARTS;
int P2RemainingShipCells = NUM_SHIP_PARTS;


// Check if a ship can be placed at a position
bool IsLegalShipPos(char board[BOARD_HEIGHT][BOARD_WIDTH], int x, int y, unsigned char ship) {
	// TODO: implement IsLegalShipPos
	// TODO: test IsLegalShipPos

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
bool PlaceShip(char (&board)[BOARD_HEIGHT][BOARD_WIDTH], int x, int y, unsigned char ship) {
	// TODO: implement PlaceShip
	// TODO: test PlaceShip

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
void PlaceAllShips(char (&board)[BOARD_HEIGHT][BOARD_WIDTH]) {}

// Output board for user
void DisplayBoard(char board[BOARD_HEIGHT][BOARD_WIDTH]) {
	// FIXME: display only hits and misses if the displaying the opposing player's board
	// if you're viewing your own board on your turn, it should also show where the ships are

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
			char cell = board[j][i];

			cout << cell << ' ';
		}
		cout << endl;
	}
}

// Set winner to the player that won the game, or 0 if the game is not over
void GameOver(unsigned char board1[BOARD_HEIGHT][BOARD_WIDTH], unsigned char board2[BOARD_HEIGHT][BOARD_WIDTH], int &winner) {
	if (P1RemainingShipCells == 0) {
		winner = 2;
	}
	else if (P2RemainingShipCells == 0) {
		winner = 1;
	}
	else {
		winner = 0;
	}
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

// Fire missile at opposing player's board, returning hit or miss
bool FireMissile(char (&targetBoard)[BOARD_HEIGHT][BOARD_WIDTH], int x, int y) {
	// FIXME: FireMissile should decrement the RemainingShipCells for the player being fired at if a hit
	// I think instead of passing references to boards we should pass the player, since the boards are global variables
	// another, maybe better, idea is to use a GetBoard(int player) func that returns a reference to a given player's board
	// this function would then be passed only the player, x, and y
	// other functions that don't need to know the player are passed a reference to a board

	char cell = targetBoard[x][y];
	bool hit = cell != EMPTY;

	if (hit) {
		targetBoard[x][y] = HIT;
	}
	else {
		targetBoard[x][y] = MISS;
	}

	return hit;
}

// Initialize game boards with empty cells
void InitializeBoard(char board[BOARD_HEIGHT][BOARD_WIDTH]){
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

	// test functions (temporary)
	DisplayBoard(P1Board);
	cout << endl;

	bool hit = FireMissile(P1Board, 0, 0);

	DisplayBoard(P1Board);

	// should output "Miss." (board is initialized to empty)
	if (hit) {
		cout << "Hit!";
	}
	else {
		cout << "Miss.";
	}
	cout << endl;

	/*
	while not GameOver(P1Board, P2Board):
		if turn == player1:
			currentBoard = &P1Board
			opposingBoard = &P2Board
		else:
			currentBoard = &P2Board
			opposingBoard = &P1Board

		DisplayBoard(currentBoard)


		position = GetInputPosition()

		hit = FireMissile(opposingBoard, position)

		output if a hit or miss

		output "Switch to player {opposite player to current player} and press enter:"
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