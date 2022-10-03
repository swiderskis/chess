#include<stdlib.h>

#include "PieceQueen.hpp"

// Constructor
PieceQueen::PieceQueen(char colour) : Piece(colour) {}

// Methods
char PieceQueen::getName() {
    switch(mColour) {
    case 'W':
        return 'Q';
        break;
    case 'B':
        return 'q';
        break;
    }
}

bool PieceQueen::validPieceMove(int dRow, int dCol, bool playerMove) {
    if (dRow == 0 || dCol == 0) {
        return true;
    } else if (abs(dRow) - abs(dCol) != 0) {
        return false;
    } else {
        return true;
    }
}
