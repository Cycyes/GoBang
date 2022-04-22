#ifndef AI_H
#define AI_H

#include "base.h"
#include "BoardPosition.h"
#include "GoBangBoard.h"
#include <QThread>

struct Score_Info {
    QString name;
    int str_num;
    int score;
    QString str[10];
};

const Score_Info score_info[] = {
    {"ChengFive", 1, 5000000, {"11111"}},
    {"HuoFour", 1, 100000, {"011110"}},
    {"ChongFore", 5, 10000, {"01111-", "-11110", "10111", "11011", "11101"}},
    {"DanHuoThree", 1, 8000, {"01110"}},
    {"TiaoHuoThree", 2, 7000, {"1011", "1101"}},
    {"MianHuoThree", 10, 500, {"00111-", "-11100", "01011-", "-11010", "01101-", "-10110", "10011", "11001", "10101", "-01110-"}},
    {"HuoTwo", 3, 50, {"001100", "01010", "1001"}},
    {"MianTwo", 7, 10, {"00011-", "-11000", "00101-", "-10100", "01001-", "-10010", "10001"}}
};
const int score_info_num = 8;

class AI : public QThread {
private:
    bool is_black;
    int depth;
    int gobang_cnt;
    BoardPosition next;
    GoBangBoard gobang_board;
public:
    void initboard();
    void set_depth(int d);
    void set_id(bool is);
    void set_cnt(int cnt);
    void takePiece(int x, int y);
    void putPiece(int x, int y, int id);
    bool near(BoardPosition p);
    int evaluate_direction(QString s);
    int evaluate_position(BoardPosition p, int id);
    int evaluate_board(int id);
    int MinMax_Search(int id, int depth);
    BoardPosition get_next_move(int id);
    BoardPosition get_first_move();
    BoardPosition ai_run();
};

#endif // AI_H
