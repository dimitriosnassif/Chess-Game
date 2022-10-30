/* Fichier : MainDisplay.h
 * Date : 06/05/2022
 * Nom : Dimitrios Nassif */


#ifndef MAINDISPLAY_H
#define MAINDISPLAY_H

#include <QPushButton>
#include <QMainWindow>
#include "ui_MainDisplay.h"
#include "DisplayLogic.h"

class ChessLogic;
class MainDisplay : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainDisplay(QWidget *parent = nullptr);

public slots:
    void checkClicked(const QPoint &box);
    void startNewGame();

protected:
    Ui::ChessINF1015 *ui;

private:
    ChessDisplay *display_;
    ChessLogic *logic_;
    QPoint clickCheck_;
    ChessDisplay::HighlightField *selectedBox_;
    QPushButton *button_;
};

#endif
