#ifndef GOBANGAI_H
#define GOBANGAI_H

#include <cmath>
#include "base.h"
#include "Point.h"
#include "GoBangBoard.h"

//status of the board
const int status_num = 17;
enum status {
    other,
    ai_win,
    ai_lose,
    ai_flex4,
    human_flex4,
    ai_block4,
    human_block4,
    ai_flex3,
    human_flex3,
    ai_block3,
    human_block3,
    ai_flex2,
    human_flex2,
    ai_block2,
    human_block2,
    ai_flex1,
    human_flex1
};

//game results
enum GameResult {
    result_human_win,
    result_ai_win,
    result_draw
};

//directions
const int dir_num = 4;
const int direction[dir_num][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
enum Directions {
    Right,
    Up,
    UpRight,
    UpLeft
};

//evaluate weight
const int weight[status_num] = {0, 1000000, -1000000, 50000, -100000, 400, -100000, 400, -8000, 20, -50, 20, -50, 1, -3, 1, -3};

//the most valuable points
const int Point_num = 20;
struct Points {
    Point point[Point_num] = {};
    int score[Point_num] = {};
};

struct Evaluation {
    int score;
    GameResult result;
    int state[8];
};

class GoBangAi {
private:
    //board information
    bool is_black;
    int gobang_cnt;
    int GoBangboard[Grid_num][Grid_num];

    //evaluate results
    Points points;
    Point select_point;
    int select_point_score;

    //evaluate array: record the score of a position with six adjacent pieces
    int tuple6type[Type_num][Type_num][Type_num][Type_num][Type_num][Type_num];
public:
    GoBangAi();
    //game logic
    void set_id(bool is);
    void set_cnt(int cnt);
    void init();
    void takePiece(int x, int y);
    void putPiece(int x, int y, int id);
    void copyBoard(int source[Grid_num][Grid_num], int board[Grid_num][Grid_num]);
    void reverseBoard(int source[Grid_num][Grid_num], int board[Grid_num][Grid_num]);

    //evaluate
    void set_eval_board(int board[Grid_num][Grid_num], int boardwith_border[Grid_num + 2][Grid_num + 2]);
    int gettuplescore(int humannum, int ainum, int c);
    int evaluateOnePos(int board[Grid_num][Grid_num], int row, int col, int c);
    Evaluation evaluateBoard(int board[Grid_num][Grid_num]);

    //search
    Points seekPoints(int board[Grid_num][Grid_num]);
    int MinMax_Search_with_Purning(int board[Grid_num][Grid_num], int depth, int alpha, int beta);
    QList<Point> seek_kill_points(int board[Grid_num][Grid_num]);
    bool find_kill(int board[Grid_num][Grid_num], int depth);
    Point ai_run();
};

#endif // GOBANGAI_H
