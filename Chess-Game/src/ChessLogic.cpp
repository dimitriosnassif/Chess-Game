/* Fichier : ChessLogic.cpp
 * Date : 06/05/2022
 * Nom : Dimitrios Nassif */

#include "ChessLogic.h"
#include "Board.h"

ChessLogic::ChessLogic(QObject *parent) : QObject(parent), board_(0)
{

}

// methode getter de l'echequier.
Board *ChessLogic::getBoard() const
{
    return board_;
}

// methode qui initialise l'echequier et place les pieces selon un Fen code specifique.
void ChessLogic::newGame()
{
    initBoard();

    /* en utilisant la methode generateRandomFen (Board.h), nous voulons pouvoir simuler
     * des postions sur l'echequier qui consiste seulement d'un roi et deux autres pieces quelconque */

    getBoard()->encodeFen("6n1/2k5/4KP1R/1p3pQ1/q7/P3P1P1/1r5r/4b2n w - - 0 1");

    /* rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 (FEN d'un echequier normal pour reference) */
}

// methode qui initialise l'echequier.
void ChessLogic::initBoard()
{
    setBoard(new Board(8,8, this));
}

// methode setter de l'echequier.
void ChessLogic::setBoard(Board *board)
{
    if(board == board_)
        return;
    if(board_)
        delete board_;
    board_ = board;
    emit boardModified(board_);
}

