#ifndef GOBANGBOARD_H
#define GOBANGBOARD_H

#include "base.h"
#include "Point.h"

class GoBangBoard {
private:
    int black_player_id;
    int board[Grid_num][Grid_num];
public:
    GoBangBoard();
    void initboard();
    void putPiece(int x, int y, int id);
    void takePiece(int x, int y);
    void setBlackPlayerID(int player_id);
    int getBlackPlayerID() const;
    int getBoardPositionID(int x, int y) const;

    bool isInside(int r, int c) const;
    bool isInside(const Point &c) const;
    bool isAvaliable(const Point &c) const;
    bool win(const Point &move, const int id);
};

#endif // GOBANGBOARD_H
