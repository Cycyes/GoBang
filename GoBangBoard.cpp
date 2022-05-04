#include "GoBangBoard.h"
#include <cstring>

GoBangBoard::GoBangBoard() {

}

void GoBangBoard::initboard() {
    memset(board, 0, sizeof(board));
}

void GoBangBoard::putPiece(int x, int y, int id) {
    board[y][x] = id;
}

void GoBangBoard::takePiece(int x, int y) {
    board[y][x] = No_Player;
}

void GoBangBoard::setBlackPlayerID(int player_id) {
    this->black_player_id = player_id;
}

int GoBangBoard::getBlackPlayerID() const {
    return this->black_player_id;
}

int GoBangBoard::getBoardPositionID(int x, int y) const {
    return board[y][x];
}

bool GoBangBoard::isInside(int r, int c) const {
    return r >= 0 && r < Grid_num && c >= 0 && c < Grid_num;
}

bool GoBangBoard::isInside(const Point& c) const {
    return c.x >= 0 && c.x < Grid_num && c.y >= 0 && c.y < Grid_num;
}

bool GoBangBoard::isAvaliable(const Point& c) const {
    return c.x >= 0 && c.x < Grid_num && c.y >= 0 && c.y < Grid_num && board[c.y][c.x] == No_Player;
}

bool GoBangBoard::win(const Point& move, const int id) {
    const int dr[] = {-1, 1, 0, 0, 1, 1, -1, -1};
    const int dc[] = {0, 0, -1, 1, 1, -1, 1, -1};
    int r, c, r0 = move.y, c0 = move.x, cnt;
    bool is_win = false;

    for(int i = 0; i < 8; i++) {
        cnt = 1;
        r = r0 + dr[i];
        c = c0 + dc[i];
        while(isInside(r, c) && board[r][c] == id) {
            cnt++;
            r += dr[i];
            c += dc[i];
        }
        r = r0 - dr[i];
        c = c0 - dc[i];
        while(isInside(r, c) && board[r][c] == id) {
            cnt++;
            r -= dr[i];
            c -= dc[i];
        }
        if(cnt >= 5) {
            is_win = true;
            break;
        }
    }
    return is_win;
}
