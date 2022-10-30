/* Fichier : Board.h
 * Date : 06/05/2022
 * Nom : Dimitrios Nassif */


#ifndef BOARD_H
#define BOARD_H


#include <QObject>
#include <QVector>

class Board : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int ranks READ ranks NOTIFY ranksChanged)
    Q_PROPERTY(int columns READ columns NOTIFY columnsChanged)

public:
    explicit Board(int ranks = 8, int columns = 8, QObject *parent = 0);

    int ranks() const { return ranks_; }
    int columns() const { return columns_; }
    char positionData(int column, int rank) const;
    void setFieldData(int column, int rank, char value);
    void movePiece(int fromColumn, int fromRank, int toColumn, int toRank);
    void encodeFen(const QString &fen);
    void generateRandomFen(int numOfGenerate);
protected:
    void setRanks(int newRanks);
    void setColumns(int newColumns);
    void initializeBoard();
    bool setInternalPosition(int column, int rank, char value);

signals:
    void ranksChanged(int);
    void columnsChanged(int);
    void boardReset();
    void dataChanged(int c, int r);

private:
    int ranks_, columns_;
    QVector<char> boardData_;
    bool search(char c, int a, int b);
    void print();
};

#endif
