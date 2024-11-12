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
bool PlaceShip(char board[BOARD_SIZE][BOARD_SIZE], int x, int y, unsigned char shipLength, bool isHorizontal) {
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
void PlaceAllShips(char board[BOARD_SIZE][BOARD_SIZE]) {
    const int shipSizes[] = {5, 4, 4, 3, 2};  // ship lengths

    for (int i = 0; i < 5; i++) {
        bool placed = false;
        while (!placed) {
            int x = rand() % BOARD_SIZE;
            int y = rand() % BOARD_SIZE;
            bool isHorizontal = rand() % 2 == 0;

            placed = PlaceShip(board, x, y, static_cast<unsigned char>(shipSizes[i]), isHorizontal);
        }
    }
}

// Output board for user
void DisplayBoard(char board[BOARD_SIZE][BOARD_SIZE], bool displayShips) {
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

			if (!displayShips && cell == SHIP) {
				cell = EMPTY;
			}

			cout << cell << ' ';
		}
		cout << endl;
	}
}

// Set winner to the player that won the game, or 0 if the game is not over
void GameOver(int &winner) {
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
	invalid = invalid || !isdigit(position.at(1));
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
// InputPosition is set to "Quit" or "Q" if the user inputs "quit"
void GetInputPosition(char opponentBoard[BOARD_SIZE][BOARD_SIZE], int &x, int &y, string& inputPosition) {
	string inputStr;
	bool valid;

	int inX;
	int inY;

	valid = false;

	while (!valid) {
		cout << "(enter 'q'/'quit' to quit)" << endl;
		cout << "Enter position: ";

		cin >> inputStr;

		if (inputStr == "q" || inputStr == "quit") {
			inX = -1;
			inY = -1;
			break;
		}

		valid = !ParsePosition(inputStr, inX, inY);
		valid = valid && opponentBoard[inX][inY] != HIT && opponentBoard[inX][inY] != MISS;

		if (!valid) {
			cout << "Invalid position! Try again." << endl;
		}
	}

	inputStr.at(0) = toupper(inputStr.at(0));
	inputPosition = inputStr;
	x = inX;
	y = inY;
}

// Fire missile at opposing player's board, returning hit or miss
bool FireMissile(char targetBoard[BOARD_SIZE][BOARD_SIZE], int x, int y, int &remainingShipCells) {
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

int SwapPlayer(int player) {
	if (player == 1) {
		return 2;
	}
	else {
		return 1;
	}
}

int main()
{
	int x;
	int y;
	bool turn = true;
	int player = 1;
	string inputPosition = "none";
	bool hit;
	int winner = 0;

	srand(static_cast<unsigned int>(time(0)));

	InitializeBoard(P1Board);
	InitializeBoard(P2Board);

	PlaceAllShips(P1Board);
	PlaceAllShips(P2Board);


	char (*currentBoard)[BOARD_SIZE][BOARD_SIZE] = &P1Board;
	char (*opposingBoard)[BOARD_SIZE][BOARD_SIZE] = &P2Board;
	int *opposingShipCells = &P2RemainingShipCells;

	// Continue until a winner is found
	while (winner == 0) {
		if (inputPosition != "none") {
			cout << "Player " << SwapPlayer(player);
			cout << " fired at " << inputPosition << ": ";

			if (hit) {
				cout << "Hit";
			}
			else {
				cout << "Miss";
			}

			cout << '!' << endl;
		}

		// Player 1's turn
		if (turn) {  
			currentBoard = &P1Board;
			opposingBoard = &P2Board;
			opposingShipCells = &P2RemainingShipCells;

		// Player 2's turn
		} else {  
			currentBoard = &P2Board;
			opposingBoard = &P1Board;
			opposingShipCells = &P1RemainingShipCells;
		}
		cout << "PLayer " << player << "'s turn!";
		cout << endl << endl;

		// Display boards
		cout << "Opponent board:" << endl;
        DisplayBoard(*opposingBoard, false);
		cout << endl;

		cout << "Your board:" << endl;
		DisplayBoard(*currentBoard, true);
		cout << endl;
		cout << opposingShipCells << endl;

        // Get player's input position
        GetInputPosition(*opposingBoard, x, y, inputPosition);

		if (inputPosition.at(0) == 'Q') {
			break;
		}

        // Fire missile at the opposing player's board and check for hit or miss
		hit = FireMissile(*opposingBoard, x, y, *opposingShipCells);

        // Output whether it's a hit or miss
        if (hit) {
            cout << "Hit!";
        } else {
            cout << "Miss!";
        }
		cout << endl << endl;

        // Check if the game is over
        GameOver(winner);

        // If no winner, switch turns
        if (winner == 0) {
			player = SwapPlayer(player);

			cout << "Switch to Player " << player << " and press Enter: ";

            // Wait for the user to press Enter to switch turns
            cin.ignore(); // Ignore the newline left in the buffer
            cin.get(); // Wait for the user to press Enter

			// Clear the terminal using ANSI escape codes
			// Might be OS dependent. probably works on all unix machines
			cout << "\033[H\033[2J\033[3J" ;

            // Switch turns
            turn = !turn; // Toggle the turn between Player 1 and Player 2
        }
    }

	if (winner != 0) {
		// Announce the winner
		cout << "Player " << winner << " wins!" << endl;
	}
	else {
		// winner is unmodified (0) if the user exits early
		cout << "Exiting..." << endl;
	}




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