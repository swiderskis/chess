#include <stdlib.h>

#include "PiecePawn.hpp"

// Constructor
PiecePawn::PiecePawn(char colour) : Piece(colour), direction(setDirection()) {}

// Methods
char PiecePawn::getName() {
    switch(mColour) {
    case 'W':
        return 'P';
        break;
    case 'B':
        return 'p';
        break;
    }
}

bool PiecePawn::validPieceMove(int dRow, int dCol, bool playerMove) {
    if (dRow == 0) {
        return false;
    } else if (dRow == direction*2 && dCol == 0 && hasMoved == false) {
        if (playerMove == true) {
            hasMoved = true;
        }

        return true;
    } else if (dRow == direction && abs(dCol) < 2) {
        if (playerMove == true) {
            hasMoved = true;
        }

        return true;
    } else {
        return false;
    }
}

int PiecePawn::setDirection() {
    switch (getColour()) {
    case 'W':
        return 1;
        break;
    case 'B':
        return -1;
        break;
    }
}
