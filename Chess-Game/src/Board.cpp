/* Fichier : Board.cpp
 * Date : 06/05/2022
 * Nom : Dimitrios Nassif */

#include "Board.h"

Board::Board(int ranks, int columns, QObject *parent)
    : QObject(parent), ranks_(ranks), columns_(columns)
{
    initializeBoard();
}

char Board::positionData(int column, int rank) const
{
    return boardData_.at((rank-1)*columns()+(column-1));
}

void Board::setFieldData(int column, int rank, char value)
{
    if(setInternalPosition(column, rank, value))
        emit dataChanged(column, rank);
}

void Board::movePiece(int fromColumn, int fromRank, int toColumn, int toRank)
{
    setFieldData(toColumn, toRank, positionData(fromColumn, fromRank));
    setFieldData(fromColumn, fromRank, ' ');
}

void Board::setRanks(int newRanks)
{
    if(ranks() == newRanks)
        return;
    ranks_ = newRanks;
    initializeBoard();
    emit ranksChanged(ranks_);
}

void Board::setColumns(int newColumns)
{
    if(columns() == newColumns)
        return;
    columns_ = newColumns;
    initializeBoard();
    emit columnsChanged(columns_);
}

void Board::initializeBoard()
{
    boardData_.fill(' ', ranks()*columns());
    emit boardReset();
}

bool Board::setInternalPosition(int column, int rank, char value)
{
    int index = (rank-1) * columns() + (column-1);
    if(boardData_.at(index) == value)
        return false;

    boardData_[index] = value;
    return true;
}

/* Forsyth-Edwards Notation est une certaine notation qui nous donne
 * toutes les informations sur une postion specifique sur l'echequier */

void Board::encodeFen(const QString &fencode)
{
    int index = 0;
    int jump = 0;
    const int countColumn = columns();
    QChar fenChar;

    for(int rank = ranks(); rank >0; --rank) {
        for(int column = 1; column <= countColumn; ++column) {
            if(jump > 0) {
                fenChar = ' ';
                jump--;
            } else {
                fenChar = fencode.at(index++);
                if(fenChar.isDigit()) {
                    jump = fenChar.toLatin1()-'0';
                    fenChar = ' ';
                    jump--;
                }
            }
            setInternalPosition(column, rank, fenChar.toLatin1());
        }
        QChar next = fencode.at(index++);
        if(next != '/' && next != ' ') {
            initializeBoard();
            return;
        }
    }
    emit boardReset();
}

/* methode qui va nous permettre de generer des positions random sur l'echequier
 * a chaque nouveau match ou numOfGenerate et le nombre de Fen code qu'il faut generer, et une methode
 * print() nous retourne un string qu'on pourra placer dans la methode encodeFen() */

void Board::generateRandomFen(int numOfGenerate)
{


}

