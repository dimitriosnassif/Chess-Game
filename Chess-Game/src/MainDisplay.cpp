/* Fichier : MainDisplay.
 * Date : 06/05/2022
 * Nom : Dimitrios Nassif */

#include "MainDisplay.h"
#include "Board.h"
#include "DisplayLogic.h"
#include "ChessLogic.h"

#include <QLayout>

MainDisplay::MainDisplay(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::ChessINF1015), selectedBox_(0)
{
    ui->setupUi(this);
    display_ = new ChessDisplay;
    connect(display_, &ChessDisplay::clicked, this, &MainDisplay::checkClicked);

    // nous instantions nos classes et placons les composantes sur le maindisplay
    logic_ = new ChessLogic(this);
    logic_->newGame();
    display_->setBoard(logic_->getBoard());
    setCentralWidget(display_);
    display_->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    display_->setFieldSize(QSize(105,105));
    layout()->setSizeConstraint(QLayout::SetFixedSize);

    /* initialisation d'un button qui va nous permettre de commencer un nouveau match et rearranger les pieces
     * randomly (donc le slot handleButton devrait integrer la methode generateRandomFen). De ce fait
     * lorsque le boutton est clicker le randomizer est declencher. */

    button_ = new QPushButton("Start New Game", this);
    button_->setGeometry(QRect(QPoint(900,25), QSize(200,50)));
    connect(button_, &QPushButton::released, this, &MainDisplay::startNewGame);

    // on relie une lettre a une piece (on commence par les pieces noires).
    display_->placePiece('p', QIcon(":/pieces/Chess_pdt45.svg")); // pion
    display_->placePiece('k', QIcon(":/pieces/Chess_kdt45.svg")); // roi
    display_->placePiece('q', QIcon(":/pieces/Chess_qdt45.svg")); // reine
    display_->placePiece('r', QIcon(":/pieces/Chess_rdt45.svg")); // tour
    display_->placePiece('n', QIcon(":/pieces/Chess_ndt45.svg")); // chevalier
    display_->placePiece('b', QIcon(":/pieces/Chess_bdt45.svg")); // fou

    // on relie une lettre a une piece (les pieces blancs).
    display_->placePiece('P', QIcon(":/pieces/Chess_plt45.svg")); // pion
    display_->placePiece('K', QIcon(":/pieces/Chess_klt45.svg")); // roi
    display_->placePiece('Q', QIcon(":/pieces/Chess_qlt45.svg")); // reine
    display_->placePiece('R', QIcon(":/pieces/Chess_rlt45.svg")); // tour
    display_->placePiece('N', QIcon(":/pieces/Chess_nlt45.svg")); // chevalier
    display_->placePiece('B', QIcon(":/pieces/Chess_blt45.svg")); // fou
}

void MainDisplay::checkClicked(const QPoint &box)
{
    if(clickCheck_.isNull()) {
        if(display_->board()->positionData(box.x(), box.y()) != ' ') {
            clickCheck_ = box;
            selectedBox_ = new ChessDisplay::HighlightField(box.x(), box.y(), QColor(0, 100, 0, 50));
            display_->addHighlight(selectedBox_);
        }
    } else {
        if(box != clickCheck_) {
            display_->board()->movePiece(clickCheck_.x(), clickCheck_.y(), box.x(), box.y());
        }
        clickCheck_ = QPoint();
        display_->hideHighlight(selectedBox_);
        delete selectedBox_;
        selectedBox_ = nullptr;
    }
}

void MainDisplay::startNewGame()
{

}
