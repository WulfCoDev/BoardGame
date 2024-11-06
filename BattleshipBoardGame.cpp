/****************************************************************
File: BattleShipBoardGame
Description:An implementation of the classic game Battleship

Authors: Christian Alexander, Alexander Newman
Class: CSCI-110-71
Date: 10/23/2024

I hereby certify that this program is entirely my own work.
*****************************************************************/

#include <iostream>
#include <string>
#include <cctype>

using namespace std;


const int BOARD_SIZE = 10;
const int NUM_SHIP_PARTS = 5 + 4 + 4 + 3 + 2;	// length of all five ships
const char SHIP = 'S';
const char HIT = 'X';
const char MISS = 'O';
const char EMPTY = '~';

char P1Board[BOARD_SIZE][BOARD_SIZE];
char P2Board[BOARD_SIZE][BOARD_SIZE];

int P1RemainingShipCells = NUM_SHIP_PARTS;
int P2RemainingShipCells = NUM_SHIP_PARTS;


// Check if a ship can be placed at a position
bool IsLegalShipPos(char board[BOARD_SIZE][BOARD_SIZE], int x, int y, unsigned char shipLength, bool isHorizontal) {
    int checkX = x;
    int checkY = y;

    for (int i = 0; i < shipLength; i++) {
        // Check boundaries
        if (checkX < 0 || checkX >= BOARD_SIZE || checkY < 0 || checkY >= BOARD_SIZE) {
            return false;
        }
        // Check if the spot is already occupied
        if (board[checkX][checkY] != EMPTY) {
            return false;
        }

        // Update position based on orientation
        if (isHorizontal) {
            checkX += 1;
        } else {
            checkY += 1;
        }
    }
    return true;
}

// Place a ship at a location on the board, returning false if the placement fails
bool PlaceShip(char (&board)[BOARD_SIZE][BOARD_SIZE], int x, int y, unsigned char shipLength, bool isHorizontal) {
    if (!IsLegalShipPos(board, x, y, shipLength, isHorizontal)) {
        return false;
    }

    int curX = x;
    int curY = y;

    for (int i = 0; i < shipLength; i++) {
        board[curX][curY] = SHIP;

        if (isHorizontal) {
            curX += 1;
        } else {
            curY += 1;
        }
    }

    return true;
}

// Initialize a board with random ship locations
void PlaceAllShips(char (&board)[BOARD_SIZE][BOARD_SIZE]) {
    const int shipSizes[] = {5, 4, 4, 3, 2};  // ship lengths
    srand(time(0));

    for (int i = 0; i < 5; i++) {
        bool placed = false;
        while (!placed) {
            int x = rand() % BOARD_SIZE;
            int y = rand() % BOARD_SIZE;
            bool isHorizontal = rand() % 2 == 0;

            placed = PlaceShip(board, x, y, shipSizes[i], isHorizontal);
        }
    }
}

// Output board for user
void DisplayBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
	// FIXME: display only hits and misses if the displaying the opposing player's board
	// if you're viewing your own board on your turn, it should also show where the ships are

	// Display column headers
	cout << "  ";
	for (int i = 0; i < BOARD_SIZE; i++) {
		cout << i + 1 << " ";
	}
	
	cout << endl;
	
	// Display rows with row numbers and cell status
	// Iterating through rows
	for (int i = 0; i < BOARD_SIZE; i++) { 
		// Output row header
		cout << static_cast<char>('A' + i) << ' ';

		// Iterating through columns
		for (int j = 0; j < BOARD_SIZE; j++) {
			char cell = board[i][j];

			cout << cell << ' ';
		}
		cout << endl;
	}
}

// Set winner to the player that won the game, or 0 if the game is not over
void GameOver(char board1[BOARD_SIZE][BOARD_SIZE], char board2[BOARD_SIZE][BOARD_SIZE], int &winner) {
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
bool ParsePosition(string position, int &x, int &y) {
	// input validation
	bool invalid = !isalpha(position.at(0));
	cout << invalid << endl;
	invalid = invalid || !isdigit(position.at(1));
	cout << invalid << endl;
	invalid = invalid || !(position.size() == 2 || position.size() == 3);

	if (position.size() == 3) {
		invalid = invalid || !isdigit(position.at(2));
	}

	if (invalid) {
		return invalid;
	}

	// Converting letter to row index and number to column index
	x = tolower(position.at(0)) - 'a';

	if (position.size() == 2) {
		y = tolower(position.at(1)) - '1';
	}
	else {
		// the only y coord with two characters is 10, which is index 9
		y = 9;
	}

	return invalid;
}

// Get the input position from the user
void GetInputPosition(char currentBoard[BOARD_SIZE][BOARD_SIZE], int &x, int &y) {
	string inputStr;
	bool valid;

	int inX;
	int inY;

	valid = false;

	while (!valid) {
		cout << "Enter position: ";

		cin >> inputStr;
		valid = !ParsePosition(inputStr, inX, inY);
		valid = valid && currentBoard[inX][inY] != HIT && currentBoard[inX][inY] != MISS;

		if (!valid) {
			cout << "Invalid position! Try again." << endl;
		}
	}

	x = inX;
	y = inY;
}

// Fire missile at opposing player's board, returning hit or miss
bool FireMissile(char (&targetBoard)[BOARD_SIZE][BOARD_SIZE], int x, int y, int &remainingShipCells) {
    // I think instead of passing references to boards we should pass the player, since the boards are global variables
	// another, maybe better, idea is to use a GetBoard(int player) func that returns a reference to a given player's board
	// this function would then be passed only the player, x, and y
	// other functions that don't need to know the player are passed a reference to a board
	char cell = targetBoard[x][y];
    bool hit = false;

    if (cell == SHIP) {
        targetBoard[x][y] = HIT;
        remainingShipCells--;
        hit = true;
    } else if (cell == EMPTY) {
        targetBoard[x][y] = MISS;
    }

    return hit;
}

// Initialize game boards with empty cells
void InitializeBoard(char board[BOARD_SIZE][BOARD_SIZE]){
	for (int i = 0; i < BOARD_SIZE; i++){
		for (int j = 0; j < BOARD_SIZE; j++){
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
	int winner = 0;

	InitializeBoard(P1Board);
	InitializeBoard(P2Board);

	PlaceAllShips(P1Board);
	PlaceAllShips(P2Board);

	// test functions (temporary)
	DisplayBoard(P1Board);
	cout << endl;

	GetInputPosition(P1Board, x, y);

	bool hit = FireMissile(P1Board, x, y);

	DisplayBoard(P1Board);
	cout << endl;
	cout << x << ' ' << y << endl;

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