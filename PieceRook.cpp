#include "PieceRook.hpp"

// Constructor
PieceRook::PieceRook(char colour) : Piece(colour) {}

// Methods
char PieceRook::getName() {
    switch(mColour) {
    case 'W':
        return 'R';
        break;
    case 'B':
        return 'r';
        break;
    }
}

bool PieceRook::validPieceMove(int dRow, int dCol, bool playerMove) {
    if (dRow != 0 && dCol != 0) {
        return false;
    } else {
        return true;
    }
}
