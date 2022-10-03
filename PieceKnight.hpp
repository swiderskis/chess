#ifndef PIECEKNIGHT_HPP
#define PIECEKNIGHT_HPP

#include "Piece.hpp"

class PieceKnight : public Piece {
public:
    // Constructor
    PieceKnight(char colour);

    // Methods
    char getName();

    bool validPieceMove(int dRow, int dCol, bool playerMove);
};

#endif
