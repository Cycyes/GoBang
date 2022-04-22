#include "ai.h"
#include <list>

using namespace std;

void AI::takePiece(int x, int y) {
    gobang_board.takePiece(x, y);
}

void AI::putPiece(int x, int y, int id) {
    gobang_board.putPiece(x, y, id);
}

void AI::initboard() {
    gobang_board.initboard();
}

void AI::set_depth(int d) {
    this->depth = d;
}

void AI::set_id(bool is) {
    this->is_black = is;
}

void AI::set_cnt(int cnt) {
    this->gobang_cnt = cnt;
}

bool AI::near(BoardPosition p) {
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            if(i == 0 && j == 0)
                continue;
            if(gobang_board.isInside(p.y + j, p.x + i) && !gobang_board.isAvaliable({p.x + i, p.y + j}))
                return true;
        }
    }
    return false;
}

int AI::evaluate_direction(QString s) {
    int score = 0;
    for(int i = 0; i < score_info_num; i++) {
        for(int j = 0; j < score_info[i].str_num; j++) {
            if(s.contains(score_info[i].str[j])) {
                score += score_info[i].score;
                break;
            }
        }
    }
    return score;
}

int AI::evaluate_position(BoardPosition p, int id) {
    int point = 0;
    int weight = position_value[p.y][p.x];
    for(int dir = 0; dir < 4; dir++) {
        QString s = "";
        int colStart = p.x - direction[dir][0] * 4;
        int rowStart = p.y - direction[dir][1] * 4;
        int colEnd = p.x + direction[dir][0] * 4;
        int rowEnd = p.y + direction[dir][1] * 4;
        for(int colnow = colStart, rownow = rowStart; colnow != colEnd || rownow != rowEnd; colnow += direction[dir][0], rownow += direction[dir][1]) {
            if(gobang_board.isInside(rownow, colnow)) {
                int now_position_id = gobang_board.getBoardPositionID(colnow, rownow);
                if(now_position_id == id)
                    s += "1";
                else if(now_position_id == No_Player)
                    s += "0";
                else
                    s += "-";
            }
            else
                s += "#";
        }
        point += evaluate_direction(s);
    }
    return point * weight;
}

int AI::evaluate_board(int id) {
    int point_ally = 0, point_enemy = 0;
    for(int i = 0; i < Grid_num; i++) {
        for(int j = 0; j < Grid_num; j++) {
            int now_player_id = gobang_board.getBoardPositionID(i, j);
            int other_id = AI_Player + H1_Player - id;
            if(now_player_id == id)
                point_ally += evaluate_position({i, j}, id);
            else if(now_player_id == other_id)
                point_enemy += evaluate_position({i, j}, other_id);
        }
    }
    int point = 10 * point_ally - point_enemy;
    return point;
}

int AI::MinMax_Search(int id, int depth) {
    int best = Negative_Infinity;
    if(depth == this->depth)
        return evaluate_board(id);
    list <BoardPosition> children;
    for(int i = 0; i < Grid_num; i++) {
        for(int j = 0; j < Grid_num; j++) {
            BoardPosition now = {i, j};
            if(near(now) && gobang_board.isAvaliable(now))
                children.emplace_back(now);
        }
    }
    for(auto it = children.begin(); it != children.end(); it++) {
        int other_id = AI_Player + H1_Player - id;
        gobang_board.putPiece((*it).x, (*it).y, id);
        int score = -MinMax_Search(other_id, depth + 1);
        gobang_board.takePiece((*it).x, (*it).y);
        if(score > best) {
            best = score;
            this->next = *it;
        }
    }
    return best;
}

BoardPosition AI::get_next_move(int id) {
    MinMax_Search(id, 0);
    return next;
}

BoardPosition AI::get_first_move() {
    return {Grid_num / 2 - 1, Grid_num / 2 - 1};
}

BoardPosition AI::ai_run() {
    if(gobang_cnt == 0)
        return get_first_move();
    else
        return get_next_move(AI_Player);
}
