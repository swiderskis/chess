#ifndef PIECEROOK_HPP
#define PIECEROOK_HPP

#include "Piece.hpp"

class PieceRook : public Piece {
public:
    // Constructor
    PieceRook(char colour);

    // Methods
    char getName();

    bool validPieceMove(int dRow, int dCol, bool playerMove);
};

#endif
