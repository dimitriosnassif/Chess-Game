QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chess
TEMPLATE = app


SOURCES += main.cpp \
    Board.cpp \
    ChessLogic.cpp \
    DisplayLogic.cpp \
    MainDisplay.cpp

HEADERS  += \
    Board.h \
    ChessLogic.h \
    DisplayLogic.h \
    MainDisplay.h

FORMS += \
    MainDisplay.ui

RESOURCES += pieces.qrc
