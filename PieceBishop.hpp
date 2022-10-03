#ifndef PIECEBISHOP_HPP
#define PIECEBISHOP_HPP

#include "Piece.hpp"

class PieceBishop : public Piece {
public:
    // Constructor
    PieceBishop(char colour);

    // Methods
    char getName();

    bool validPieceMove(int dRow, int dCol, bool playerMove);
};

#endif
