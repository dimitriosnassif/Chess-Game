/* Fichier : ChessLogic.h
 * Date : 06/05/2022
 * Nom : Dimitrios Nassif */


#ifndef CHESSLOGIC_H
#define CHESSLOGIC_H

#include <QObject>
class Board;

class ChessLogic : public QObject
{
    Q_OBJECT
public:
    explicit ChessLogic(QObject *parent = 0);
    Board* getBoard() const;

public slots:
    virtual void newGame();

signals:
    void boardModified(Board*);

protected:
    virtual void initBoard();
    void setBoard(Board *board);

private:
    Board* board_;
};

#endif
