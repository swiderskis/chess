#ifndef PIECE_HPP
#define PIECE_HPP

// Holds information related to pieces on the board
class Piece {
protected:
    char mColour;

public:
    // Constructor
    Piece(char colour);

    // Methods
    // Return piece colour
    char getColour();

    // Return name of piece
    virtual char getName() = 0;

    // Check if input move is possible for piece
    virtual bool validPieceMove(int dRow, int dCol, bool playerMove) = 0;
};

#endif
