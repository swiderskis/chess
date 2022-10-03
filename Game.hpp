#ifndef GAME_HPP
#define GAME_HPP

#include "Piece.hpp"
#include "PieceKing.hpp"
#include "PieceQueen.hpp"
#include "PieceBishop.hpp"
#include "PieceKnight.hpp"
#include "PieceRook.hpp"
#include "PiecePawn.hpp"

#include "Menu.hpp"

class Game {

private:
    Piece* board[8][8];

    Menu menu;

    bool checkmateWhite = false, checkmateBlack = false, checkWhite = false, checkBlack = false;

public:
    // Constructor
    Game();

    // Methods

    // Prints current board state
    void printBoard();

    // Runs the full game until checkmate is reached
    void game();

    // Prompts player to move a piece, and checks to ensure the move is valid
    void movePiece(char colour);

    // Checks if piece selected can make a legal move
    bool checkPieceCanMove(int rowCurr, int colCurr, char colour);

    // Checks if piece selected belongs to player
    // errorWhen bool used to determine what type of inputs are invalid
    bool checkPieceColour(int r, int c, char colour, bool errorWhen, bool printError);

    // Checks if move is valid in context of board
    bool checkBoardValidMove(int rowCurr, int colCurr, int rowNew, int colNew, int dRow, int dCol, bool printError);

    // Checks if king is in check
    bool isKingInCheck(char colour);
};

#endif
