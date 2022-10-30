/* Fichier : DisplayLogic.h
 * Date : 06/05/2022
 * Nom : Dimitrios Nassif */

#ifndef DISPLAYLOGIC_H
#define DISPLAYLOGIC_H

#include <QWidget>
#include <QPointer>
#include <QMap>
#include <QIcon>
#include <QObject>

class Board;

class ChessDisplay : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QSize fieldSize READ fieldSize WRITE setFieldSize NOTIFY fieldSizeChanged)

public:
    class MoveHighlight {
    public:
        MoveHighlight() {}
        virtual ~MoveHighlight() {}
        virtual int type() const { return 0; }
    };

    class HighlightField : public MoveHighlight {
    public:
        enum { Type = 1 };
        HighlightField(int column, int rank, QColor color)
            : field_(column, rank), color_(color) {}
        inline int column() const { return field_.x(); }
        inline int rank() const { return field_.y(); }
        inline QColor color() const { return color_; }
        int type() const { return Type; }
    private:
        QPoint field_;
        QColor color_;
    };

    explicit ChessDisplay(QWidget *parent = 0);
    void setBoard(Board*);
    Board* board() const;
    QSize fieldSize() const;
    QSize sizeHint() const;
    QRect fieldRect(int column, int rank) const;
    void placePiece(char type, const QIcon &image);
    QIcon piece(char type) const;
    QPoint fieldAt(const QPoint &point) const;

    void addHighlight(MoveHighlight *highlight);
    void hideHighlight(MoveHighlight *highlight);
    inline MoveHighlight *highlight(int index) const { return highlights_.at(index); }
    inline int highlightCount() const { return highlights_.size(); }

public slots:
    void setFieldSize(QSize fieldSize);

signals:
    void fieldSizeChanged(QSize fieldSize);
    void clicked(const QPoint &);

protected:
    void paintEvent(QPaintEvent *event);
    void mouseRelease(QMouseEvent *release);

    virtual void paintField(QPainter *paint, int column, int rank);
    virtual void paintPiece(QPainter *paint, int column, int rank);
    virtual void paintHighlights(QPainter *paint);

private:
    QPointer<Board> board_;
    QSize fieldSize_;
    QMap<char,QIcon> pieces_;
    QList<MoveHighlight*> highlights_;
};

#endif
