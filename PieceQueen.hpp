#ifndef PIECEQUEEN_HPP
#define PIECEQUEEN_HPP

#include "Piece.hpp"

class PieceQueen : public Piece {
public:
    // Constructor
    PieceQueen(char colour);

    // Methods
    char getName();

    bool validPieceMove(int dRow, int dCol, bool playerMove);
};

#endif
