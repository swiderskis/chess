/*
INSERT SUMMARY HERE
*/

#include <iostream>
#include <string>
#include <cmath>
#include <stdlib.h>

using namespace std;

// Holds information related to pieces on the board
class Piece {
protected:
    char mColour;

public:
    // Constructor
    Piece(char colour) : mColour(colour) {}

    // Methods
    // Return piece colour
    char getColour() {
        return mColour;
    }

    // Return name of piece
    virtual char getName() = 0;

    // Check if input move is possible for piece
    virtual bool validPieceMove(int dRow, int dCol) = 0;
};

class PieceKing : public Piece {
public:
    // Constructor
    PieceKing(char colour) : Piece(colour) {}

    // Methods
    char getName() {
        switch(mColour) {
        case 'W':
            return 'K';
            break;
        case 'B':
            return 'k';
            break;
        }
    }

    bool validPieceMove(int dRow, int dCol) {
        if (abs(dRow) > 1 || abs(dCol) > 1) {
            return false;
        } else {
            return true;
        }
    }
};

class PieceQueen : public Piece {
public:
    // Constructor
    PieceQueen(char colour) : Piece(colour) {}

    // Methods
    char getName() {
        switch(mColour) {
        case 'W':
            return 'Q';
            break;
        case 'B':
            return 'q';
            break;
        }
    }

    bool validPieceMove(int dRow, int dCol) {
        if (dRow == 0 || dCol == 0) {
            return true;
        } else if (abs(dRow) - abs(dCol) != 0) {
            return false;
        } else {
            return true;
        }
    }
};

class PieceBishop : public Piece {
public:
    // Constructor
    PieceBishop(char colour) : Piece(colour) {}

    // Methods
    char getName() {
        switch(mColour) {
        case 'W':
            return 'B';
            break;
        case 'B':
            return 'b';
            break;
        }
    }

    bool validPieceMove(int dRow, int dCol) {
        if (dRow == 0 || dCol == 0) {
            return false;
        } else if (abs(dRow) - abs(dCol) != 0) {
            return false;
        } else {
            return true;
        }
    }
};

class PieceKnight : public Piece {
public:
    // Constructor
    PieceKnight(char colour) : Piece(colour) {}

    // Methods
    char getName() {
        switch(mColour) {
        case 'W':
            return 'N';
            break;
        case 'B':
            return 'n';
            break;
        }
    }

    bool validPieceMove(int dRow, int dCol) {
        if ((abs(dRow) == 2 && abs(dCol) == 1) || (abs(dRow) == 1 && abs(dCol) == 2)) {
            return true;
        } else {
            return false;
        }
    }
};

class PieceRook : public Piece {
public:
    // Constructor
    PieceRook(char colour) : Piece(colour) {}

    // Methods
    char getName() {
        switch(mColour) {
        case 'W':
            return 'R';
            break;
        case 'B':
            return 'r';
            break;
        }
    }

    bool validPieceMove(int dRow, int dCol) {
        if (dRow != 0 && dCol != 0) {
            return false;
        } else {
            return true;
        }
    }
};

class PiecePawn : public Piece {
private:
    bool hasMoved;
    int direction;
public:
    // Constructor
    PiecePawn(char colour) : Piece(colour), hasMoved(false), direction(setDirection()) {}

    // Methods
    char getName() {
        switch(mColour) {
        case 'W':
            return 'P';
            break;
        case 'B':
            return 'p';
            break;
        }
    }

    bool validPieceMove(int dRow, int dCol) {
        if (dRow == 0) {
            return false;
        } else if (dRow == direction*2 && dCol == 0 && hasMoved == false) {
            hasMoved = true;
            return true;
        } else if (dRow == direction && abs(dCol) < 2) {
            hasMoved = true;
            return true;
        } else {
            return false;
        }
    }

    // Sets direction of pawn based on colour
    int setDirection() {
        switch (getColour()) {
        case 'W':
            return 1;
            break;
        case 'B':
            return -1;
            break;
        }
    }
};

class Menu {
private:
    string invalidCharInput = "ERROR: Invalid column input!\n";
    string invalidIntInput = "ERROR: Invalid row input!\n";
public:
    // Methods

    // Checks if char input is valid
    // Taken from https://www.codegrepper.com/code-examples/cpp/check+if+char+in+string+c%2B%2B
    bool validUserInput(char input, string validInput) {
        if (validInput.find(input) != std::string::npos) {
            return true;
        } else {
            cout << invalidCharInput;
            return false;
        }
    }

    // Checks if int input is valid
    bool validUserInput(int input, int minValidInput, int maxValidInput) {
        if (input < minValidInput || input > maxValidInput) {
            cout << invalidIntInput;
            return false;
        } else {
            return true;
        }
    }

    // Converts char col input into int input
    int charToIntInput(char input) {
        string chars = "ABCDEFGH";
        return chars.find(input);

    }
    // Clears console
    // Taken from https://stackoverflow.com/questions/6486289/how-can-i-clear-console
    void clearConsole() {
#if defined _WIN32
        system("cls");
        //clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        system("clear");
        //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences
#elif defined (__APPLE__)
        system("clear");
#endif
    }
};

class Game {

private:
    Piece* board[8][8];

    Menu menu;

    string inputTextWhite = "\nWhite, ";
    string inputTextBlack = "\nBlack, ";
    string inputTextCurrPos = "input the position of the piece you would like to move:\n";
    string inputTextNewPos = "\nInput the position you would like to move this piece to:\n";
    string validInput = "ABCDEFGH";

    string errorCheckPieceCanMove = "ERROR: This piece cannot make a legal move!\n";
    string errorCheckPieceOppColour = "ERROR: This piece does not belong to you!\n";
    string errorCheckPiecePlayerColour = "ERROR: This position contains one of your pieces!\n";
    string errorCheckPieceColourEmpty = "ERROR: There is no piece in this square!\n";
    string errorInvalidMove = "ERROR: Invalid move!\n";
    string errorObstructed = "ERROR: Piece is blocked from moving to this space!\n";

public:
    // Constructor
    Game() {

        for (int r = 0; r < 8; r++) {
            for (int c = 0; c < 8; c++) {
                board[r][c] = 0;
            }
        }

        // Initialise white
        board[0][0] = new PieceRook('W');
        board[0][1] = new PieceBishop('W');
        board[0][2] = new PieceKnight('W');
        board[0][3] = new PieceQueen('W');
        board[0][4] = new PieceKing('W');
        board[0][5] = new PieceKnight('W');
        board[0][6] = new PieceBishop('W');
        board[0][7] = new PieceRook('W');

        for (int c = 0; c < 8; c++) {
            board[1][c] = new PiecePawn('W');
        }

        // Initialise black
        board[7][0] = new PieceRook('B');
        board[7][1] = new PieceBishop('B');
        board[7][2] = new PieceKnight('B');
        board[7][3] = new PieceQueen('B');
        board[7][4] = new PieceKing('B');
        board[7][5] = new PieceKnight('B');
        board[7][6] = new PieceBishop('B');
        board[7][7] = new PieceRook('B');

        for (int c = 0; c < 8; c++) {
            board[6][c] = new PiecePawn('B');
        }
    }

    // Methods

    // Prints current board state
    void printBoard() {
        menu.clearConsole();

        cout << "---   +---+---+---+---+---+---+---+---+\n";

        for (int r = 7; r >= 0; r--) {
            for (int c = 0; c < 8; c++) {
                if (c == 0) {
                    cout << " " << r + 1 << "    ";
                }

                if (board[r][c] != 0) {
                    cout << "| " << board[r][c]->getName() << " ";
                } else {
                    cout << "|   ";
                }

                if(c == 7) {
                    cout << "|";
                }
            }
            cout << "\n---   +---+---+---+---+---+---+---+---+\n";
        }
        cout << "                                       \n";
        cout << "      | A | B | C | D | E | F | G | H |\n";
    }

    // Prompts player to move a piece, and checks to ensure the move is valid
    void movePiece(char colour) {
        bool validCol = false, validRow = false, pieceCanMove = false, pieceBelongsToPlayer = false, pieceValidMove = false, pieceObstructed = true;

        char colCurrStr, colNewStr;

        int rowCurr, colCurr, rowNew, colNew;
        int dRow, dCol;

        const int minRow = 1, maxRow = 8;

        printBoard();

        switch (colour) {
        case 'W':
            cout << inputTextWhite;
            break;
        case 'B':
            cout << inputTextBlack;
            break;
        }

        cout << inputTextCurrPos;

        // Checks if input is in bounds of board, if piece selected can move, and if piece belongs to player
        while (validCol == false || validRow == false || pieceCanMove == false || pieceBelongsToPlayer == false) {
            cin >> colCurrStr >> rowCurr;

            validCol = menu.validUserInput(colCurrStr, validInput);
            if (validCol == true) {
                colCurr = menu.charToIntInput(colCurrStr);
            } else {
                continue;
            }

            validRow = menu.validUserInput(rowCurr, minRow, maxRow);
            if (validRow == true) {
                rowCurr--;
            } else {
                continue;
            }

            if (validCol == true && validRow == true) {
                pieceCanMove = checkPieceCanMove(rowCurr, colCurr, colour);
                pieceBelongsToPlayer = checkPieceColour(rowCurr, colCurr, colour, false);

            }
        }

        validCol = false;
        validRow = false;

        cout << inputTextNewPos;

        // Checks if input is in bounds of board, and if piece can move to location
        while (validCol == false || validRow == false || pieceBelongsToPlayer == true || pieceValidMove == false || pieceObstructed == true) {
            cin >> colNewStr >> rowNew;

            validCol = menu.validUserInput(colNewStr, validInput);
            if (validCol == true) {
                colNew = menu.charToIntInput(colNewStr);
            } else {
                continue;
            }

            validRow = menu.validUserInput(rowNew, minRow, maxRow);
            if (validRow == true) {
                rowNew--;
            } else {
                continue;
            }

            if (validCol == true && validRow == true) {
                dRow = rowNew - rowCurr;
                dCol = colNew - colCurr;

                pieceValidMove = board[rowCurr][colCurr]->validPieceMove(dRow, dCol);

                // Check piece is moving to different spot
                // Put into if else statement so error does not double print
                if (dRow == 0 && dCol == 0) {
                    pieceValidMove = false;
                } else {
                    pieceBelongsToPlayer = checkPieceColour(rowNew, colNew, colour, true);
                }

                // Special move checks for pawns
                if (board[rowCurr][colCurr]->getName() == 'P' || board[rowCurr][colCurr]->getName() == 'p') {
                    if ((dCol == 0 && board[rowNew][colNew] != 0) || (dCol != 0 && board[rowNew][colNew] == 0)) {
                        pieceValidMove = false;
                    }
                }

                // Check to ensure piece is not blocked from moving to desired location (except for knights)
                if ((board[rowCurr][colCurr]->getName() != 'N' || board[rowCurr][colCurr]->getName() != 'n') && pieceValidMove == true) {
                    pieceObstructed = checkPieceObstructed(rowCurr, colCurr, dRow, dCol);
                }

                if (pieceValidMove == false) {
                    cout << errorInvalidMove;
                }
            }
        }

        board[rowNew][colNew] = board[rowCurr][colCurr];
        board[rowCurr][colCurr] = 0;

    }

    // Runs the full game until checkmate is reached
    void game() {
        bool checkmateWhite = false, checkmateBlack = false, checkWhite = false, checkBlack = false;
        char turn = 'W';

        string winWhite = "White wins!\n";
        string winBlack = "Black wins!\n";

        while (checkmateWhite == false || checkmateBlack == false) {

            movePiece(turn);

            switch (turn) {
            case 'W':
                turn = 'B';
                break;
            case 'B':
                turn = 'W';
                break;
            }
        }

        if (checkmateBlack == true) {
            cout << winWhite;
        }

        if (checkmateWhite == true) {
            cout << winBlack;
        }

    }

    //UNFINISHED Checks if piece selected can make a legal move
    bool checkPieceCanMove(int r, int c, char colour) {
        return true;
    }

    // Checks if piece selected belongs to player
    // errorWhen bool used to determine what type of inputs are invalid
    bool checkPieceColour(int r, int c, char colour, bool errorWhen) {
        if (board[r][c] == 0) {
            if (errorWhen == false) {
                cout << errorCheckPieceColourEmpty;
            }
            return false;

        } else if (board[r][c]->getColour() != colour) {
            if (errorWhen == false) {
                cout << errorCheckPieceOppColour;
            }
            return false;

        } else {
            if (errorWhen == true) {
                cout << errorCheckPiecePlayerColour;
            }
            return true;
        }
    }

    // Checks piece is not blocked from moving to desired location
    bool checkPieceObstructed(int rowCurr, int colCurr, int dRow, int dCol) {
        bool pieceObstructed = false;

        while (abs(dRow) > 1 || abs(dCol) > 1) {
            if (dRow > 0) {
                dRow--;
            } else if (dRow < 0) {
                dRow++;
            }

            if (dCol > 0) {
                dCol--;
            } else if (dCol < 0) {
                dCol++;
            }

            if (board[rowCurr + dRow][colCurr + dCol] != 0) {
                pieceObstructed = true;
                break;
            }
        }

        cout << errorObstructed;

        return pieceObstructed;
    }
};

int main() {
    Game newGame;

    newGame.game();

    return 0;
}
