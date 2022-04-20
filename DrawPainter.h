#ifndef DRAWPAINTER_H
#define DRAWPAINTER_H

#include <QBrush>
#include <QColor>
#include <QPainter>
#include <QPen>

#include "base.h"
#include "GoBangBoard.h"
#include "BoardPosition.h"

class DrawPainter : public QPainter {
public:
    DrawPainter(QPaintDevice* parent = Q_NULLPTR);
    void init();
    void DrawBoard();
    void DrawKeyPos();
    void DrawMark();
    void DrawAIPreMove();
    void DrawChessPieces(const GoBangBoard& c);
    void DrawLastMove(const BoardPosition& c, bool is_black);
};

#endif // DRAWPAINTER_H
