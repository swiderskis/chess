#ifndef PIECEPAWN_HPP
#define PIECEPAWN_HPP

#include "Piece.hpp"

class PiecePawn : public Piece {
private:
    bool hasMoved = false;
    int direction;
public:
    // Constructor
    PiecePawn(char colour);

    // Methods
    char getName();

    bool validPieceMove(int dRow, int dCol, bool playerMove);

    // Sets direction of pawn based on colour
    int setDirection();
};

#endif
