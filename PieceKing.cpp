#include <stdlib.h>

#include "PieceKing.hpp"

// Constructor
PieceKing::PieceKing(char colour) : Piece(colour) {}

// Methods
char PieceKing::getName() {
    switch(mColour) {
    case 'W':
        return 'K';
        break;
    case 'B':
        return 'k';
        break;
    }
}

bool PieceKing::validPieceMove(int dRow, int dCol, bool playerMove) {
    if (abs(dRow) > 1 || abs(dCol) > 1) {
        return false;
    } else {
        return true;
    }
}
