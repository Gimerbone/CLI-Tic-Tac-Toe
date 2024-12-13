#include <iostream>
#include <limits>
using std::cout;
using std::cin;
using std::max;
using std::min;

char board[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
void printBoard();
bool isOccupied(int boardIndex);
bool hasEmptySpaces();
char checkWinner();
void playerMove();
void computerMove();
int minimax(bool isMaximizing);
int getBestMove();

int main(void) {
    cout << "\n" << "Welcome to CLI Tic Tac Toe !" << "\n";
    cout << "Made by Gimerbone, source: https://github.com/Gimerbone/CLI-Tic-Tac-Toe/tree/master" << "\n";
    // Initialize Game
    printBoard();

    while (true) {
        playerMove();
        printBoard();
        if (checkWinner() != ' ') {
            break;
        }

        cout << "Opponent's Turn:" << "\n";
        computerMove();
        printBoard();
        if (checkWinner() != ' ') {
            break;
        }
    }

    char winner = checkWinner();
    if (winner == 'X') {
        cout << "Player wins!\n";
    } else if (winner == 'O') {
        cout << "Computer wins!\n";
    } else {
        cout << "It's a draw!\n";
    }

    return 0;
}

void printBoard() {
    cout << "\n";
    cout << "     |     |     \n";
    cout << "  " << board[0] << "  |  " << board[1] << "  |  " << board[2] << "  \n";
    cout << "     |     |     \n";
    cout << "-----|-----|-----\n";
    cout << "     |     |     \n";
    cout << "  " << board[3] << "  |  " << board[4] << "  |  " << board[5] << "  \n";
    cout << "     |     |     \n";
    cout << "-----|-----|-----\n";
    cout << "     |     |     \n";
    cout << "  " << board[6] << "  |  " << board[7] << "  |  " << board[8] << "  \n";
    cout << "     |     |     \n";
    cout << "\n";
}

bool hasEmptySpaces() {
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            return true;
        }
    }
    return false;
}

bool isOccupied(int boardIndex) {
    return board[boardIndex] != ' ';
}

char checkWinner() {
    const int winPatterns[8][3] = {
        {0, 1, 2}, // Row 1
        {3, 4, 5}, // Row 2
        {6, 7, 8}, // Row 3
        {0, 3, 6}, // Column 1
        {1, 4, 7}, // Column 2
        {2, 5, 8}, // Column 3
        {0, 4, 8}, // Diagonal 1
        {2, 4, 6}  // Diagonal 2
    };

    // Check for 'X' or 'O' winner
    for (int i = 0; i < 8; ++i) {
        if (board[winPatterns[i][0]] != ' ' &&
            board[winPatterns[i][0]] == board[winPatterns[i][1]] &&
            board[winPatterns[i][1]] == board[winPatterns[i][2]]) {
            return board[winPatterns[i][0]];
        }
    }

    // If no winner but board is full, it's a draw
    return hasEmptySpaces() ? ' ' : 'D';
}

void playerMove() {
    int userInput;
    cout << "Now is Your Turn" << "\n";
    cout << "Enter the position you want to play (1-9): ";
    
    while (true) {
        if (!(cin >> userInput) || userInput < 1 || userInput > 9 || isOccupied(userInput - 1)) {
            cout << "Invalid input! Please enter a number between 1 and 9 for an empty spot: ";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            break;
        }
    }

    board[userInput - 1] = 'X';
}

void computerMove() {
    int bestMove = getBestMove();
    board[bestMove] = 'O';
}

// Minimax algorithm to evaluate the best move
int minimax(bool isMaximizing) {
    char winner = checkWinner();
    if (winner == 'X') return -10;
    if (winner == 'O') return 10;
    if (!hasEmptySpaces()) return 0;

    if (isMaximizing) {
        int bestScore = -1000;
        for (int i = 0; i < 9; ++i) {
            if (board[i] == ' ') {
                board[i] = 'O';
                int score = minimax(false);
                board[i] = ' ';
                bestScore = max(score, bestScore);
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int i = 0; i < 9; ++i) {
            if (board[i] == ' ') {
                board[i] = 'X';
                int score = minimax(true);
                board[i] = ' ';
                bestScore = min(score, bestScore);
            }
        }
        return bestScore;
    }
}

// Function to get the best move for the AI
int getBestMove() {
    int bestScore = -1000;
    int move = 0;

    for (int i = 0; i < 9; ++i) {
        if (board[i] == ' ') {
            board[i] = 'O';
            int score = minimax(false);
            board[i] = ' ';
            if (score > bestScore) {
                bestScore = score;
                move = i;
            }
        }
    }
    return move;
}
