/* Fichier : main.cpp
 * Date : 06/05/2022
 * Nom : Dimitrios Nassif */

#include <QApplication>
#include "MainDisplay.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainDisplay mw;
    mw.show();
    return a.exec();
}
