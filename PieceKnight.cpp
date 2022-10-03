#include <stdlib.h>

#include "PieceKnight.hpp"

// Constructor
PieceKnight::PieceKnight(char colour) : Piece(colour) {}

// Methods
char PieceKnight::getName() {
    switch(mColour) {
    case 'W':
        return 'N';
        break;
    case 'B':
        return 'n';
        break;
    }
}

bool PieceKnight::validPieceMove(int dRow, int dCol, bool playerMove) {
    if ((abs(dRow) == 2 && abs(dCol) == 1) || (abs(dRow) == 1 && abs(dCol) == 2)) {
        return true;
    } else {
        return false;
    }
}
