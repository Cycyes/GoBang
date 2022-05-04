#ifndef DRAWPAINTER_H
#define DRAWPAINTER_H

#include <QBrush>
#include <QColor>
#include <QPainter>
#include <QPen>

#include "base.h"
#include "GoBangBoard.h"
#include "Point.h"

class DrawPainter : public QPainter {
public:
    DrawPainter(QPaintDevice* parent = Q_NULLPTR);
    void init();
    void DrawBoard();
    void DrawPieces(const GoBangBoard& c);
    void DrawLastMove(const Point& c, bool is_black);
};

#endif // DRAWPAINTER_H
