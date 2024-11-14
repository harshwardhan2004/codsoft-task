#include <iostream>
#include <vector>

char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
char currentPlayer = 'X';

void displayBoard() {
    std::cout << "\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << board[i][j];
            if (j < 2) std::cout << " | ";
        }
        std::cout << "\n";
        if (i < 2) std::cout << "--+---+--\n";
    }
    std::cout << "\n";
}

bool placeMarker(int slot) {
    int row = (slot - 1) / 3;
    int col = (slot - 1) % 3;

    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = currentPlayer;
        return true;
    } else {
        std::cout << "Slot already taken! Try a different slot.\n";
        return false;
    }
}

bool checkWin() {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == board[i][1] && board[i][1] == board[i][2]) || 
            (board[0][i] == board[1][i] && board[1][i] == board[2][i])) {
            return true;
        }
    }
    // Check diagonals
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2]) ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0])) {
        return true;
    }
    return false;
}

bool checkDraw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return false;
            }
        }
    }
    return true;
}

void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

void resetBoard() {
    char slot = '1';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = slot++;
        }
    }
    currentPlayer = 'X';
}

int main() {
    char playAgain;
    std::cout << "Welcome to Tic-Tac-Toe!\n";

    do {
        resetBoard();
        bool gameWon = false;
        bool gameDraw = false;

        while (!gameWon && !gameDraw) {
            displayBoard();
            int slot;
            std::cout << "Player " << currentPlayer << ", enter a slot (1-9): ";
            std::cin >> slot;

            if (slot < 1 || slot > 9) {
                std::cout << "Invalid slot! Please choose a slot between 1 and 9.\n";
                continue;
            }

            if (placeMarker(slot)) {
                gameWon = checkWin();
                gameDraw = checkDraw();

                if (!gameWon && !gameDraw) {
                    switchPlayer();
                }
            }
        }

        displayBoard();
        if (gameWon) {
            std::cout << "Congratulations! Player " << currentPlayer << " wins!\n";
        } else if (gameDraw) {
            std::cout << "It's a draw!\n";
        }

        std::cout << "Do you want to play again? (Y/N): ";
        std::cin >> playAgain;
    } while (playAgain == 'Y' || playAgain == 'y');

    std::cout << "Thank you for playing Tic-Tac-Toe!\n";
    return 0;
}

