/*
INSERT SUMMARY HERE
*/

#include <iostream>

using namespace std;

std::ostream& bold_on(std::ostream& os)
{
    return os << "\e[1m";
}

std::ostream& bold_off(std::ostream& os)
{
    return os << "\e[0m";
}

// Holds information related to pieces on the board
class Piece {
protected:
    char mColour;

public:
    // Constructor
    Piece(char colour) : mColour(colour) {}

    // Methods
    char getColour() {
        return mColour;
    }

    virtual char getName() = 0;
};

class PieceKing : public Piece {
public:
    // Constructor
    // Taken from https://cppsecrets.com/users/22319897989712197103975756505164103109971051084699111109/Chess-Game-in-C00.php
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
};

class PiecePawn : public Piece {
public:
    // Constructor
    PiecePawn(char colour) : Piece(colour) {}

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
};

class Board {
private:
    Piece* position[8][8];

public:
    // Constructor
    Board() {
        for (int r = 0; r < 8; r++) {
            for (int c = 0; c < 8; c++) {
                position[r][c] = 0;
            }
        }
        // Initialise white
        position[0][0] = new PieceRook('W');
        position[0][1] = new PieceBishop('W');
        position[0][2] = new PieceKnight('W');
        position[0][3] = new PieceQueen('W');
        position[0][4] = new PieceKing('W');
        position[0][5] = new PieceKnight('W');
        position[0][6] = new PieceBishop('W');
        position[0][7] = new PieceRook('W');

        for (int c = 0; c < 8; c++) {
            position[1][c] = new PiecePawn('W');
        }

        // Initialise black
        position[7][0] = new PieceRook('B');
        position[7][1] = new PieceBishop('B');
        position[7][2] = new PieceKnight('B');
        position[7][3] = new PieceQueen('B');
        position[7][4] = new PieceKing('B');
        position[7][5] = new PieceKnight('B');
        position[7][6] = new PieceBishop('B');
        position[7][7] = new PieceRook('B');

        for (int c = 0; c < 8; c++) {
            position[6][c] = new PiecePawn('B');
        }
    }

    // Methods
    void print() {
        cout << "---+---+---+---+---+---+---+---+---+\n";

        for (int r = 7; r >= 0; r--) {
            for (int c = 0; c < 8; c++) {
                if (c == 0) {
                    cout << " " << r + 1 << " ";
                }
                if (position[r][c] != 0) {
                    cout << "| " << position[r][c]->getName() << " ";
                } else {
                    cout << "|   ";
                }

                if(c == 7) {
                    cout << "|";
                }
            }
            cout << "\n---+---+---+---+---+---+---+---+---+\n";
        }
        cout << "   | A | B | C | D | E | F | G | H |\n";
    }

};

int main() {
    Board gameBoard;

    gameBoard.print();

    return 0;
}
