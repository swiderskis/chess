#include "Piece.hpp"

// Constructor
Piece::Piece(char colour) : mColour(colour) {}

// Methods
char Piece::getColour() {
    return mColour;
}
