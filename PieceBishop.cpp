#include <stdlib.h>

#include "PieceBishop.hpp"

// Constructor
PieceBishop::PieceBishop(char colour) : Piece(colour) {}

// Methods
char PieceBishop::getName() {
    switch(mColour) {
    case 'W':
        return 'B';
        break;
    case 'B':
        return 'b';
        break;
    }
}

bool PieceBishop::validPieceMove(int dRow, int dCol, bool playerMove) {
    if (dRow == 0 || dCol == 0) {
        return false;
    } else if (abs(dRow) - abs(dCol) != 0) {
        return false;
    } else {
        return true;
    }
}
