#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to display the Tic-Tac-Toe board with position numbers
void displayBoard(char* board) {
    cout << "\nBoard:\n";
    cout << " 1 | 2 | 3 " << endl;
    cout << "-----------" << endl;
    cout << " 4 | 5 | 6 " << endl;
    cout << "-----------" << endl;
    cout << " 7 | 8 | 9 " << endl;
    cout << "\nCurrent board:\n";
    cout << " " << board[0] << " | " << board[1] << " | " << board[2] << endl;
    cout << "-----------" << endl;
    cout << " " << board[3] << " | " << board[4] << " | " << board[5] << endl;
    cout << "-----------" << endl;
    cout << " " << board[6] << " | " << board[7] << " | " << board[8] << endl;
}

// Function to check if the current player has won
bool checkWin(char* board, char symbol) {
    // Check rows
    for (int i = 0; i < 9; i += 3) {
        if (board[i] == symbol && board[i + 1] == symbol && board[i + 2] == symbol)
            return true;
    }
    // Check columns
    for (int i = 0; i < 3; i++) {
        if (board[i] == symbol && board[i + 3] == symbol && board[i + 6] == symbol)
            return true;
    }
    // Check diagonals
    if ((board[0] == symbol && board[4] == symbol && board[8] == symbol) ||
        (board[2] == symbol && board[4] == symbol && board[6] == symbol))
        return true;
    return false;
}

// Function to check if the board is full
bool checkDraw(char* board) {
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ')
            return false;
    }
    return true;
}

// Function to reset the board
void resetBoard(char* board) {
    for (int i = 0; i < 9; i++) {
        board[i] = ' ';
    }
}

// Function to get computer's move
int getComputerMove(char* board) {
    // Check for winning move or block opponent's winning move
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            board[i] = 'O';
            if (checkWin(board, 'O')) {
                board[i] = ' ';
                return i + 1;
            }
            board[i] = 'X';
            if (checkWin(board, 'X')) {
                board[i] = ' ';
                return i + 1;
            }
            board[i] = ' ';
        }
    }

    // Center control
    if (board[4] == ' ')
        return 5;

    // Fallback to random move
    int move;
    do {
        move = rand() % 9;
    } while (board[move] != ' ');

    return move + 1;
}

int main() {
    srand(time(0)); // Seed the random number generator

    char board[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    string player1, player2;
    int player1Score = 0, player2Score = 0, tiecount = 0;
    bool playAgain = true;

    cout << "Welcome to Tic-Tac-Toe!\n";

    cout << "Enter Player 1 name: ";
    cin >> player1;

    while (playAgain) {
        cout << "Select the mode:\n";
        cout << "1. Player vs Player\n";
        cout << "2. Player vs Computer\n";
        int mode;
        cin >> mode;

        if (mode == 1) {
            cout << "Enter Player 2 name: ";
            cin >> player2;
        }
        if (mode == 2) {
            cout << "Enter Player 2 name: ";
            player2 = "Computer";
        }

        while (true) {
            char currentPlayer = 'X';
            string currentPlayerName = player1;
            if (mode == 2 && currentPlayer == 'O') {
                currentPlayerName = "Computer";
            }

            while (true) {
                displayBoard(board);
                cout << "\nPlayer (" << currentPlayer << ") "<< currentPlayerName << "'s turn. Enter position (1-9): ";
                int position;

                if (mode == 1 || (mode == 2 && currentPlayer == 'X')) {
                    cin >> position;
                    // Validate input
                    if (position < 1 || position > 9 || board[position - 1] != ' ' ) {
                        cout << "Invalid move. Try again.\n";
                        continue;
                    }
                } else {
                    position = getComputerMove(board);
                }

                // Make move
                board[position - 1] = currentPlayer;

                // Check for win or draw
                if (checkWin(board, currentPlayer)) {
                    
                    displayBoard(board);
                    if (currentPlayer == 'X'){
                        cout << "\nPlayer " << player1 << " wins!\n";
                        player1Score++;}
                    else{
                        cout << "\nPlayer " << player2 << " wins!\n";
                        player2Score++;}
                    break;
                } else if (checkDraw(board)) {
                    cout << "\nThe game is a draw!\n";
                    tiecount++;
                    displayBoard(board);
                    break;
                }

                // Switch player
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                if (mode == 1) {
                    currentPlayerName = (currentPlayer == 'X') ? player1 : player2;
                } else if (mode == 2 && currentPlayer == 'O') {
                    currentPlayerName = (currentPlayer == 'X') ? player1 : "Computer";
                }
            }

            cout << "\nScore:\n";
            cout << player1 << ": " << player1Score << endl;
            cout << player2 << ": " << player2Score << endl;
            cout << "Tie " << ": " << tiecount << endl;

            char replay;
            cout << "\nDo you want to play again? (Y/N): ";
            cin >> replay;
            if (replay != 'Y' && replay != 'y')
                playAgain = false;
            else {
                resetBoard(board);
            }

            break;
        }
    }

    return 0;
}


