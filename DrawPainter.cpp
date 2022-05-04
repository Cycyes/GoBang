#include "DrawPainter.h"

//colot parameter setting
enum Color {
    Black1 = 58,
    Black2 = 64,
    White = 238
};

DrawPainter::DrawPainter(QPaintDevice *parent) : QPainter(parent) {

}

void DrawPainter::init() {
    //set color and anti-aliasing
    this->setPen(Qt::black);
    this->setRenderHint(QPainter::Antialiasing, true);
}

void DrawPainter::DrawBoard() {
    //draw board grid line
    for(int i = Board_start_X; i<= Board_end_X; i += Grid_Width) {
        this->drawLine(Board_start_X, i, Board_end_X, i);
        this->drawLine(i, Board_start_Y, i, Board_end_Y);
    }
    //draw board frame
    this->drawRect(Board_start_X - 7, Board_start_Y - 7, Board_Width + 14, Board_Width + 14);
}

void DrawPainter::DrawPieces(const GoBangBoard& c) {
    this->setPen(Qt::NoPen);
    QRadialGradient radi;

    //traverse board and draw pieces
    for(int i = 0; i < Grid_num; i++) {
        for(int j = 0; j < Grid_num; j++) {
            int now_player_id = c.getBoardPositionID(i, j);
            int black_player_id = c.getBlackPlayerID();
            if(now_player_id != No_Player) {
                if(now_player_id == black_player_id) {
                    radi.setColorAt(0, qRgb(Black1, Black1, Black1));
                    this->setBrush(radi);
                    this->drawEllipse(Board_start_X + Grid_Width * (i + 1) - Chess_Piece_Radius, Board_start_X + Grid_Width * (j + 1) - Chess_Piece_Radius, Chess_Piece_Radius * 2, Chess_Piece_Radius * 2);
                }
                else {
                    radi.setColorAt(0, qRgb(Black2, Black2, Black2));
                    this->setBrush(radi);
                    this->drawEllipse(Board_start_X + Grid_Width * (i + 1) - Chess_Piece_Radius, Board_start_X + Grid_Width * (j + 1) - Chess_Piece_Radius, Chess_Piece_Radius * 2, Chess_Piece_Radius * 2);

                    radi.setColorAt(0, qRgb(White, White, White));
                    this->setBrush(radi);
                    this->drawEllipse(Board_start_X + Grid_Width * (i + 1) - Chess_Piece_Radius, Board_start_X + Grid_Width * (j + 1) - Chess_Piece_Radius, Chess_Piece_Radius * 2, Chess_Piece_Radius * 2);
                }
            }
        }
    }
}

void DrawPainter::DrawLastMove(const Point& c, bool is_black) {
    QPen prev_pen = this->pen();
    QRadialGradient radi;

    if(is_black) {
        radi.setColorAt(0, qRgb(Black1, Black1, Black1));
        this->setPen(qRgb(Black1, Black1, Black1));
    }
    else
        radi.setColorAt(0, qRgb(Black1, Black1, Black1));

    this->setBrush(radi);
    this->drawEllipse(Board_start_X + Grid_Width * (c.x + 1) - Mark_Radius, Board_start_X + Grid_Width * (c.y + 1) - Mark_Radius, 2 * Mark_Radius, 2 * Mark_Radius);

    this->setPen(prev_pen);
}
