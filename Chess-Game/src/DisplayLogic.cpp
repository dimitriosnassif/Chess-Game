/* Fichier : DisplayLogic.cpp
 * Date : 06/05/2022
 * Nom : Dimitrios Nassif */

#include "DisplayLogic.h"
#include "Board.h"

#include <QMouseEvent>
#include <QPainter>

ChessDisplay::ChessDisplay(QWidget *parent) : QWidget(parent)
{

}

void ChessDisplay::setBoard(Board *board)
{
    if(board_ == board) return;

    if(board_) {
        // déconnectez toutes les connexions signal-slot entre board_ et this
        board_->disconnect(this);
    }
    board_ = board;
    // relier les signaux-slots
    if(board){
        connect(board, SIGNAL(dataChanged(int,int)), this, SLOT(update()));
        connect(board, SIGNAL(boardReset()), this, SLOT(update()));
    }
    updateGeometry();
}

Board *ChessDisplay::ChessDisplay::board() const
{
    return board_;
}

QSize ChessDisplay::fieldSize() const
{
    return fieldSize_;
}

void ChessDisplay::setFieldSize(QSize fieldSize)
{
    if (fieldSize_ == fieldSize) return;

    fieldSize_ = fieldSize;
    emit fieldSizeChanged(fieldSize);
    updateGeometry();
}

QSize ChessDisplay::sizeHint() const
{
    if(!board_) return QSize(50,50);
    QSize boardSize = QSize(fieldSize().width()  * board_->columns() +1,
                            fieldSize_.height() * board_->ranks()   +1);
    int rankSize = size().width()+4;
    int columnSize = fontMetrics().height()+4;
    return boardSize+QSize(rankSize, columnSize);
}

QRect ChessDisplay::fieldRect(int column, int rank) const
{
    if(!board_) return QRect();
    const QSize fs = fieldSize();
    QRect fRect = QRect(QPoint((column-1)*fs.width(), (board_->ranks()-rank)*fs.height()), fs);

    int offset = fontMetrics().maxWidth();
    return fRect.translated(offset+4, 0);
}

void ChessDisplay::placePiece(char type, const QIcon &image)
{
    pieces_.insert(type, image);
    update();
}

QIcon ChessDisplay::piece(char type) const
{
    return pieces_.value(type, QIcon());
}

void ChessDisplay::paintEvent(QPaintEvent *event)
{
    if(!board_) return;
    QPainter paint(this);

    for(int rank = board_->ranks(); rank > 0; --rank) {
        paint.save();
    }

    for(int column = 1; column <= board_->columns() ;++column) {
        paint.save();
    }

    for(int rank = 1; rank <= board_->ranks(); ++rank) {
        for(int column = 1; column <= board_->columns(); ++column) {
            paint.save();
            paintField(&paint, column, rank);
            paint.restore();
        }
    }

    paintHighlights(&paint);

    for(int rank = board_->ranks(); rank > 0; --rank) {
        for(int column = 1; column <= board_->columns(); ++column) {
            paintPiece(&paint, column, rank);
        }
    }
}

void ChessDisplay::paintField(QPainter *paint, int column, int rank)
{
    QRect box = fieldRect(column, rank);
    QColor fillBox = (column+rank) % 2 ? palette().color(QPalette::Light)
                                         : palette().color(QPalette::Mid);
    paint->setPen(palette().color(QPalette::Dark));
    paint->setBrush(fillBox);
    paint->drawRect(box);
}

void ChessDisplay::paintPiece(QPainter *paint, int column, int rank)
{
    QRect rect = fieldRect(column, rank);
    char value = board_->positionData(column, rank);
    if(value != ' ') {
        QIcon icon = piece(value);
        if(!icon.isNull()) {
            icon.paint(paint, rect, Qt::AlignCenter);
        }
    }
}

void ChessDisplay::paintHighlights(QPainter *paint)
{
    for(int h = 0; h < highlightCount(); ++h) {
        MoveHighlight *hlight = highlight(h);
        if(hlight->type() == HighlightField::Type) {
            HighlightField *fhlight = static_cast<HighlightField*>(hlight);
            QRect rect = fieldRect(fhlight->column(), fhlight->rank());
            paint->fillRect(rect, fhlight->color());
        }
    }
}

QPoint ChessDisplay::fieldAt(const QPoint &point) const
{
    if(!board_) return QPoint();

    const QSize sizeField = fieldSize();
    int offset = size().width()+4;

    if(point.x() < offset) return QPoint();

    int column = (point.x()-offset) / sizeField.width();
    int rank = point.y() / sizeField.height();

    if(column < 0 || column >= board_->columns() || rank < 0 || rank >= board_->ranks()) return QPoint();

    return QPoint(column + 1, board_->ranks() - rank);
}

void ChessDisplay::mouseRelease(QMouseEvent *release)
{
    QPoint point = fieldAt(release->pos());
    if(point.isNull()) return;
    emit clicked(point);
}

void ChessDisplay::addHighlight(ChessDisplay::MoveHighlight *highlight)
{
    highlights_.append(highlight); update();
}

void ChessDisplay::hideHighlight(ChessDisplay::MoveHighlight *highlight)
{
    highlights_.removeOne(highlight); update();
}
