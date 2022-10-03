#include "game.hpp"

// Constructor
Game::Game() {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            board[r][c] = 0;
        }
    }

    // Initialise white
    board[0][0] = new PieceRook('W');
    board[0][1] = new PieceBishop('W');
    board[0][2] = new PieceKnight('W');
    board[0][3] = new PieceQueen('W');
    board[0][4] = new PieceKing('W');
    board[0][5] = new PieceKnight('W');
    board[0][6] = new PieceBishop('W');
    board[0][7] = new PieceRook('W');

    for (int c = 0; c < 8; c++) {
        board[1][c] = new PiecePawn('W');
    }

    // Initialise black
    board[7][0] = new PieceRook('B');
    board[7][1] = new PieceBishop('B');
    board[7][2] = new PieceKnight('B');
    board[7][3] = new PieceQueen('B');
    board[7][4] = new PieceKing('B');
    board[7][5] = new PieceKnight('B');
    board[7][6] = new PieceBishop('B');
    board[7][7] = new PieceRook('B');

    for (int c = 0; c < 8; c++) {
        board[6][c] = new PiecePawn('B');
    }
}

// Methods
void Game::printBoard() {
    menu.clearConsole();

    cout << "---   +---+---+---+---+---+---+---+---+\n";

    for (int r = 7; r >= 0; r--) {
        for (int c = 0; c < 8; c++) {
            if (c == 0) {
                cout << " " << r + 1 << "    ";
            }

            if (board[r][c] != 0) {
                cout << "| " << board[r][c]->getName() << " ";
            } else {
                cout << "|   ";
            }

            if(c == 7) {
                cout << "|";
            }
        }

        cout << "\n---   +---+---+---+---+---+---+---+---+\n";
    }

    cout << "                                       \n";
    cout << "      | A | B | C | D | E | F | G | H |\n";
}

void Game::game() {
    char turn = 'W';

    string winWhite = "\nWhite wins!\n";
    string winBlack = "\nBlack wins!\n";

    while (checkmateWhite == false || checkmateBlack == false) {

        // Takes copy of board, used for possible move checks
        for (int r = 0; r < 8; r++) {
            for (int c = 0; c < 8; c++) {
                boardCopy[r][c] = board[r][c];
            }
        }

        movePiece(turn);

        switch (turn) {
        case 'W':
            turn = 'B';
            checkBlack = isKingInCheck(turn);
            break;
        case 'B':
            turn = 'W';
            checkWhite = isKingInCheck(turn);
            break;
        }
    }

    if (checkmateBlack == true) {
        printBoard();
        cout << winWhite;
    }

    if (checkmateWhite == true) {
        printBoard();
        cout << winBlack;
    }

}

void Game::movePiece(char colour) {
    bool validCol = false, validRow = false, pieceCanMove = false, pieceBelongsToPlayer = false, pieceValidMove = false, boardValidMove = true, pieceCanStopCheck = false, kingOutOfCheck = false;

    char colCurrStr, colNewStr;

    int rowCurr, colCurr, rowNew, colNew;
    int dRow, dCol;

    const int MIN_ROW = 1, MAX_ROW = 8;

    string inputTextWhite = "\nWhite, ";
    string inputTextBlack = "\nBlack, ";
    string inputTextCurrPos = "input the position of the piece you would like to move:\n";
    string inputTextNewPos = "\nInput the position you would like to move this piece to:\n";
    string validInput = "ABCDEFGH";
    string errorInvalidMove = "ERROR: Invalid move!\n";
    string errorKingInCheck = "ERROR: Your king is in check!\n";
    string whiteKingInCheck = "\nWhite's king is in check!\n";
    string blackKingInCheck = "\nBlack's king is in check!\n";

    printBoard();

    if (checkWhite == true) {
        cout << whiteKingInCheck;
    }

    if (checkBlack == true) {
        cout << blackKingInCheck;
    }

    switch (colour) {
    case 'W':
        cout << inputTextWhite;
        break;
    case 'B':
        cout << inputTextBlack;
        break;
    }

    // SELECT CURRENT PIECE
    cout << inputTextCurrPos;

    // Checks if input is in bounds of board, if piece selected can move, and if piece belongs to player
    while (validCol == false || validRow == false || pieceCanMove == false || pieceBelongsToPlayer == false || pieceCanStopCheck == false) {
        cin >> colCurrStr >> rowCurr;

        validCol = menu.validUserInput(colCurrStr, validInput);

        if (validCol == true) {
            colCurr = menu.charToIntInput(colCurrStr);
        } else {
            continue;
        }

        validRow = menu.validUserInput(rowCurr, MIN_ROW, MAX_ROW);

        if (validRow == true) {
            rowCurr--;
        } else {
            continue;
        }

        pieceBelongsToPlayer = checkPieceColour(rowCurr, colCurr, colour, false, true);

        if (pieceBelongsToPlayer == true) {
            pieceCanMove = checkPieceCanMove(rowCurr, colCurr, colour);
            pieceCanStopCheck = canPieceStopCheck(colour, rowCurr, colCurr);
        } else {
            continue;
        }

    }

    validCol = false;
    validRow = false;

    // CHOOSE NEW POSITION
    cout << inputTextNewPos;

    // Checks if input is in bounds of board, and if piece can move to location
    while (validCol == false || validRow == false || pieceBelongsToPlayer == true || pieceValidMove == false || boardValidMove == false || kingOutOfCheck == false) {
        cin >> colNewStr >> rowNew;

        validCol = menu.validUserInput(colNewStr, validInput);

        if (validCol == true) {
            colNew = menu.charToIntInput(colNewStr);
        } else {
            continue;
        }

        validRow = menu.validUserInput(rowNew, MIN_ROW, MAX_ROW);

        if (validRow == true) {
            rowNew--;
        } else {
            continue;
        }

        if (validCol == true && validRow == true) {
            dRow = rowNew - rowCurr;
            dCol = colNew - colCurr;

            // Check piece is moving to different spot
            // Put into if else statement so error does not double print
            if (dRow == 0 && dCol == 0) {
                pieceValidMove = false;
            } else {
                pieceValidMove = board[rowCurr][colCurr]->validPieceMove(dRow, dCol, true);
            }

            if (pieceValidMove == false) {
                cout << errorInvalidMove;
                continue;
            }

            pieceBelongsToPlayer = checkPieceColour(rowNew, colNew, colour, true, true);
            boardValidMove = checkBoardValidMove(rowCurr, colCurr, rowNew, colNew, dRow, dCol, true);
        }

        board[rowNew][colNew] = board[rowCurr][colCurr];
        board[rowCurr][colCurr] = 0;

        switch (colour) {
        case 'W':
            checkWhite = isKingInCheck(colour);
            break;
        case 'B':
            checkBlack = isKingInCheck(colour);
            break;
        }

        if ((checkWhite == true && colour == 'W') || (checkBlack == true && colour == 'B')) {
            cout << errorKingInCheck;

            kingOutOfCheck = false;

            revertBoard(rowCurr, colCurr, rowNew, colNew);
        } else {
            kingOutOfCheck = true;
        }
    }
}

bool Game::checkPieceCanMove(int rowCurr, int colCurr, char colour) {
    int dRow, dCol;
    bool pieceCanMove = false, pieceValidMove = false, pieceBelongsToPlayer = true, boardValidMove = false;

    string errorCheckPieceCanMove = "ERROR: This piece cannot make a legal move!\n";

    for (int rowNew = 0; rowNew < 8; rowNew++) {
        for (int colNew = 0; colNew < 8; colNew++) {
            dRow = rowNew - rowCurr;
            dCol = colNew - colCurr;

            if (dRow == 0 && dCol == 0) {
                continue;
            } else {
                pieceValidMove = board[rowCurr][colCurr]->validPieceMove(dRow, dCol, false);
                pieceBelongsToPlayer = checkPieceColour(rowNew, colNew, colour, true, false);
                boardValidMove = checkBoardValidMove(rowCurr, colCurr, rowNew, colNew, dRow, dCol, false);
            }

            if (pieceValidMove == true && pieceBelongsToPlayer == false && boardValidMove == true) {
                pieceCanMove = true;
                return pieceCanMove;
            }
        }
    }

    if (pieceCanMove == false) {
        cout << errorCheckPieceCanMove;
    }

    return pieceCanMove;
}

bool Game::checkPieceColour(int r, int c, char colour, bool errorWhen, bool printError) {
    string errorCheckPieceOppColour = "ERROR: This piece does not belong to you!\n";
    string errorCheckPiecePlayerColour = "ERROR: This position contains one of your pieces!\n";
    string errorCheckPieceColourEmpty = "ERROR: There is no piece in this square!\n";

    if (board[r][c] == 0) {
        if (errorWhen == false && printError == true) {
            cout << errorCheckPieceColourEmpty;
        }
        return false;

    } else if (board[r][c]->getColour() != colour) {
        if (errorWhen == false && printError == true) {
            cout << errorCheckPieceOppColour;
        }
        return false;

    } else {
        if (errorWhen == true && printError == true) {
            cout << errorCheckPiecePlayerColour;
        }
        return true;
    }
}

bool Game::checkBoardValidMove(int rowCurr, int colCurr, int rowNew, int colNew, int dRow, int dCol, bool printError) {
    bool pawnMoveCheck = false, pieceObstructed = false, boardValidMove = false;

    string errorObstructed = "ERROR: Piece is blocked from moving to this space!\n";

    // Special move checks for pawns
    if (board[rowCurr][colCurr]->getName() == 'P' || board[rowCurr][colCurr]->getName() == 'p') {
        if ((dCol == 0 && board[rowNew][colNew] != 0) || (dCol != 0 && board[rowNew][colNew] == 0)) {
            pawnMoveCheck = false;
        } else {
            pawnMoveCheck = true;
        }
    } else {
        pawnMoveCheck = true;
    }

    // Check to ensure piece is not blocked from moving to desired location (except for knights)
    if (board[rowCurr][colCurr]->getName() != 'N' && board[rowCurr][colCurr]->getName() != 'n') {
        while (abs(dRow) > 1 || abs(dCol) > 1) {
            if (dRow > 0) {
                dRow--;
            } else if (dRow < 0) {
                dRow++;
            }

            if (dCol > 0) {
                dCol--;
            } else if (dCol < 0) {
                dCol++;
            }

            if (board[rowCurr + dRow][colCurr + dCol] != 0) {
                pieceObstructed = true;
                if (printError == true) {
                    cout << errorObstructed;
                }
                break;
            }
        }
    } else {
        pieceObstructed = false;
    }

    if (pawnMoveCheck == true && pieceObstructed == false) {
        boardValidMove = true;
    }

    return boardValidMove;
}

bool Game::isKingInCheck(char colour) {
    int kingRow, kingCol, dRow, dCol;

    bool pieceValidMove = false, boardValidMove = false;

    // Identify king position
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            if (board[r][c] != 0 && (board[r][c]->getName() == 'K' || board[r][c]->getName() == 'k') && board[r][c]->getColour() == colour) {
                kingRow = r;
                kingCol = c;

                // Breaks loop
                r = 7;
                c = 7;
            }
        }
    }

    // Finds position of opposing pieces, and sees if they are putting the king in check
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            if (board[r][c] != 0 && board[r][c]->getColour() != colour) {
                dRow = kingRow - r;
                dCol = kingCol - c;

                pieceValidMove = board[r][c]->validPieceMove(dRow, dCol, false);
                boardValidMove = checkBoardValidMove(r, c, kingRow, kingCol, dRow, dCol, false);

                if (pieceValidMove == true && boardValidMove == true) {
                    return true;
                }
            }
        }
    }

    return false;
}

void Game::revertBoard(int rowCurr, int colCurr, int rowNew, int colNew) {
    board[rowCurr][colCurr] = boardCopy[rowCurr][colCurr];
    board[rowNew][colNew] = boardCopy[rowNew][colNew];
}

bool Game::canPieceStopCheck(char colour, int rowCurr, int colCurr) {
    bool kingInCheck = true, pieceCanStopCheck = false, pieceValidMove = false, boardValidMove = false;
    int dRow, dCol;

    string errorPieceCannotStopCheck = "ERROR: this piece cannot take your king out of check!\n";

    // Finds possible moves the selected piece can perform, and sees if any can take the king out of check
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            dRow = r - rowCurr;
            dCol = c - colCurr;

            pieceValidMove = board[rowCurr][colCurr]->validPieceMove(dRow, dCol, false);
            boardValidMove = checkBoardValidMove(rowCurr, colCurr, r, c, dRow, dCol, false);

            if (pieceValidMove == true && boardValidMove == true) {
                board[r][c] = board[rowCurr][colCurr];
                board[rowCurr][colCurr] = 0;

                kingInCheck = isKingInCheck(colour);

                revertBoard(rowCurr, colCurr, r, c);

                if (kingInCheck == false) {
                    return true;
                }
            }
        }
    }

    cout << errorPieceCannotStopCheck;

    return false;
}
