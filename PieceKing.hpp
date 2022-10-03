#ifndef PIECEKING_HPP
#define PIECEKING_HPP

#include "Piece.hpp"

class PieceKing : public Piece {
public:
    // Constructor
    PieceKing(char colour);

    // Methods
    char getName();

    bool validPieceMove(int dRow, int dCol, bool playerMove);
};

#endif
