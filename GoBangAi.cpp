#include "GoBangAi.h"

/*-----------------------------function------------------------------------*/
bool isInside(int row, int col) {
    if(row >= 0 && row < Grid_num && col >= 0 && col < Grid_num)
        return true;
    return false;
}

Point getPoint(int row, int col, int dir, int rel) {
    Point p;
    p.x = col + rel * direction[dir][1];
    p.y = row + rel * direction[dir][0];
    return p;
}
/*-----------------------------function------------------------------------*/

/*-----------------------------game logic----------------------------------*/
GoBangAi::GoBangAi() {
    init();
}

void GoBangAi::set_id(bool is) {
    is_black = is;
}

void GoBangAi::set_cnt(int cnt) {
    gobang_cnt = cnt;
}

void GoBangAi::takePiece(int x, int y) {
    GoBangboard[y][x] = No_Player;
}

void GoBangAi::putPiece(int x, int y, int id) {
    GoBangboard[y][x] = id;
}

void GoBangAi::init() {
    //init board
    memset(GoBangboard, 0, sizeof(GoBangboard));
    //inittuple6type
    memset(tuple6type, 0, sizeof(tuple6type));
    // AI win
    tuple6type[AI_Player][AI_Player][AI_Player][AI_Player][AI_Player][AI_Player] = ai_win;
    tuple6type[AI_Player][AI_Player][AI_Player][AI_Player][AI_Player][No_Player] = ai_win;
    tuple6type[No_Player][AI_Player][AI_Player][AI_Player][AI_Player][AI_Player] = ai_win;
    tuple6type[AI_Player][AI_Player][AI_Player][AI_Player][AI_Player][Border] = ai_win;
    tuple6type[Border][AI_Player][AI_Player][AI_Player][AI_Player][AI_Player] = ai_win;
    tuple6type[AI_Player][AI_Player][AI_Player][AI_Player][AI_Player][H1_Player] = ai_win;
    tuple6type[H1_Player][AI_Player][AI_Player][AI_Player][AI_Player][AI_Player] = ai_win;
    // human win
    tuple6type[H1_Player][H1_Player][H1_Player][H1_Player][H1_Player][H1_Player] = ai_lose;
    tuple6type[H1_Player][H1_Player][H1_Player][H1_Player][H1_Player][No_Player] = ai_lose;
    tuple6type[No_Player][H1_Player][H1_Player][H1_Player][H1_Player][H1_Player] = ai_lose;
    tuple6type[H1_Player][H1_Player][H1_Player][H1_Player][H1_Player][Border] = ai_lose;
    tuple6type[Border][H1_Player][H1_Player][H1_Player][H1_Player][H1_Player] = ai_lose;
    tuple6type[H1_Player][H1_Player][H1_Player][H1_Player][H1_Player][AI_Player] = ai_lose;
    tuple6type[AI_Player][H1_Player][H1_Player][H1_Player][H1_Player][H1_Player] = ai_lose;
    // flex4
    tuple6type[No_Player][AI_Player][AI_Player][AI_Player][AI_Player][No_Player] = ai_flex4;
    tuple6type[No_Player][H1_Player][H1_Player][H1_Player][H1_Player][No_Player] = human_flex4;
    // flex3
    tuple6type[No_Player][AI_Player][AI_Player][AI_Player][No_Player][No_Player] = ai_flex3;
    tuple6type[No_Player][No_Player][AI_Player][AI_Player][AI_Player][No_Player] = ai_flex3;
    tuple6type[No_Player][AI_Player][No_Player][AI_Player][AI_Player][No_Player] = ai_flex3;
    tuple6type[No_Player][AI_Player][AI_Player][No_Player][AI_Player][No_Player] = ai_flex3;
    tuple6type[No_Player][H1_Player][H1_Player][H1_Player][No_Player][No_Player] = human_flex3;
    tuple6type[No_Player][No_Player][H1_Player][H1_Player][H1_Player][No_Player] = human_flex3;
    tuple6type[No_Player][H1_Player][No_Player][H1_Player][H1_Player][No_Player] = human_flex3;
    tuple6type[No_Player][H1_Player][H1_Player][No_Player][H1_Player][No_Player] = human_flex3;
    // flex2
    tuple6type[No_Player][AI_Player][AI_Player][No_Player][No_Player][No_Player] = ai_flex2;
    tuple6type[No_Player][AI_Player][No_Player][AI_Player][No_Player][No_Player] = ai_flex2;
    tuple6type[No_Player][AI_Player][No_Player][No_Player][AI_Player][No_Player] = ai_flex2;
    tuple6type[No_Player][No_Player][AI_Player][AI_Player][No_Player][No_Player] = ai_flex2;
    tuple6type[No_Player][No_Player][AI_Player][No_Player][AI_Player][No_Player] = ai_flex2;
    tuple6type[No_Player][No_Player][No_Player][AI_Player][AI_Player][No_Player] = ai_flex2;
    tuple6type[No_Player][H1_Player][H1_Player][No_Player][No_Player][No_Player] = human_flex2;
    tuple6type[No_Player][H1_Player][No_Player][H1_Player][No_Player][No_Player] = human_flex2;
    tuple6type[No_Player][H1_Player][No_Player][No_Player][H1_Player][No_Player] = human_flex2;
    tuple6type[No_Player][No_Player][H1_Player][H1_Player][No_Player][No_Player] = human_flex2;
    tuple6type[No_Player][No_Player][H1_Player][No_Player][H1_Player][No_Player] = human_flex2;
    tuple6type[No_Player][No_Player][No_Player][H1_Player][H1_Player][No_Player] = human_flex2;
    // flex1
    tuple6type[No_Player][AI_Player][No_Player][No_Player][No_Player][No_Player] = ai_flex1;
    tuple6type[No_Player][No_Player][AI_Player][No_Player][No_Player][No_Player] = ai_flex1;
    tuple6type[No_Player][No_Player][No_Player][AI_Player][No_Player][No_Player] = ai_flex1;
    tuple6type[No_Player][No_Player][No_Player][No_Player][AI_Player][No_Player] = ai_flex1;
    tuple6type[No_Player][H1_Player][No_Player][No_Player][No_Player][No_Player] = human_flex1;
    tuple6type[No_Player][No_Player][H1_Player][No_Player][No_Player][No_Player] = human_flex1;
    tuple6type[No_Player][No_Player][No_Player][H1_Player][No_Player][No_Player] = human_flex1;
    tuple6type[No_Player][No_Player][No_Player][No_Player][H1_Player][No_Player] = human_flex1;
    // block
    int left_human_num, left_Ai_num, right_human_num, right_Ai_num;
    for (int p1 = 0; p1 < Type_num; p1++) {
        for (int p2 = 0; p2 < Type_num - 1; p2++) {
            for (int p3 = 0; p3 < Type_num - 1; p3++) {
                for (int p4 = 0; p4 < Type_num - 1; p4++) {
                    for (int p5 = 0; p5 < Type_num - 1; p5++) {
                        for (int p6 = 0; p6 < Type_num; p6++) {
                            left_human_num = left_Ai_num = right_human_num = right_Ai_num = 0;

                            if (p1 == H1_Player)
                                left_human_num++;
                            else if (p1 == AI_Player)
                                left_Ai_num++;

                            if (p2 == H1_Player)
                                left_human_num++, right_human_num++;
                            else if (p2 == AI_Player)
                                left_Ai_num++, right_Ai_num++;

                            if (p3 == H1_Player)
                                left_human_num++, right_human_num++;
                            else if (p3 == AI_Player)
                                left_Ai_num++, right_Ai_num++;

                            if (p4 == H1_Player)
                                left_human_num++, right_human_num++;
                            else if (p4 == AI_Player)
                                left_Ai_num++, right_Ai_num++;

                            if (p5 == H1_Player)
                                left_human_num++, right_human_num++;
                            else if (p5 == AI_Player)
                                left_Ai_num++, right_Ai_num++;

                            if (p6 == H1_Player)
                                right_human_num++;
                            else if (p6 == AI_Player)
                                right_Ai_num++;

                            if (p1 == Border || p6 == Border) {
                                if (p1 == Border && p6 != Border) {
                                    if (right_human_num == 0 && right_Ai_num == 4 && tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                        tuple6type[p1][p2][p3][p4][p5][p6] = ai_block4;
                                    else if (right_human_num == 4 && right_Ai_num == 0 && tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                        tuple6type[p1][p2][p3][p4][p5][p6] = human_block4;
                                    else if (right_human_num == 0 && right_Ai_num == 3 && tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                        tuple6type[p1][p2][p3][p4][p5][p6] = ai_block3;
                                    else if (right_human_num == 3 && right_Ai_num == 0 && tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                        tuple6type[p1][p2][p3][p4][p5][p6] = human_block3;
                                    else if (right_human_num == 0 && right_Ai_num == 2 && tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                        tuple6type[p1][p2][p3][p4][p5][p6] = ai_block2;
                                    else if (right_human_num == 2 && right_Ai_num == 0 && tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                        tuple6type[p1][p2][p3][p4][p5][p6] = human_block2;
                                }
                                else if (p1 != Border && p6 == Border) {
                                    if (left_human_num == 0 && left_Ai_num == 4 && tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                        tuple6type[p1][p2][p3][p4][p5][p6] = ai_block4;
                                    else if (left_human_num == 4 && left_Ai_num == 0 && tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                        tuple6type[p1][p2][p3][p4][p5][p6] = human_block4;
                                    else if (left_human_num == 0 && left_Ai_num == 3 && tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                        tuple6type[p1][p2][p3][p4][p5][p6] = ai_block3;
                                    else if (left_human_num == 3 && left_Ai_num == 0 && tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                        tuple6type[p1][p2][p3][p4][p5][p6] = human_block3;
                                    else if (left_human_num == 0 && left_Ai_num == 2 && tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                        tuple6type[p1][p2][p3][p4][p5][p6] = ai_block2;
                                    else if (left_human_num == 2 && left_Ai_num == 0 && tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                        tuple6type[p1][p2][p3][p4][p5][p6] = human_block2;
                                }
                            }
                            else {
                                if (((left_human_num == 0 && left_Ai_num == 4) || (right_human_num == 0 && right_Ai_num == 4)) && tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                    tuple6type[p1][p2][p3][p4][p5][p6] = ai_block4;
                                else if (((left_human_num == 4 && left_Ai_num == 0) || (right_human_num == 4 && right_Ai_num == 0)) && tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                    tuple6type[p1][p2][p3][p4][p5][p6] = human_block4;
                                else if (((left_human_num == 0 && left_Ai_num == 3) || (right_human_num == 0 && right_Ai_num == 3)) && tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                    tuple6type[p1][p2][p3][p4][p5][p6] = ai_block3;
                                else if (((left_human_num == 3 && left_Ai_num == 0) || (right_human_num == 3 && right_Ai_num == 0)) && tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                    tuple6type[p1][p2][p3][p4][p5][p6] = human_block3;
                                else if (((left_human_num == 0 && left_Ai_num == 2) || (right_human_num == 0 && right_Ai_num == 2)) && tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                    tuple6type[p1][p2][p3][p4][p5][p6] = ai_block2;
                                else if (((left_human_num == 2 && left_Ai_num == 0) || (right_human_num == 2 && right_Ai_num == 0)) && tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                    tuple6type[p1][p2][p3][p4][p5][p6] = human_block2;
                            }
                        }
                    }
                }
            }
        }
    }
}
/*-----------------------------game logic----------------------------------*/

/*------------------------------evaluate-----------------------------------*/
//make a board with border from the original board
void GoBangAi::set_eval_board(int board[Grid_num][Grid_num], int board_with_border[Grid_num + 2][Grid_num + 2]) {
    for (int i = 0; i < Grid_num + 2; i++)
        board_with_border[0][i] = board_with_border[16][i] = board_with_border[i][0] = board_with_border[i][16] = Border;
    for (int i = 0; i < Grid_num; i++)
        for (int j = 0; j < Grid_num; j++)
            board_with_border[i + 1][j + 1] = board[i][j];
}

//evaluate by number of pieces
int GoBangAi::gettuplescore(int humannum, int ainum, int c) {
    if(c == H1_Player && humannum == 5)
        return 9999999;
    if(c == AI_Player && ainum == 5)
        return 9999999;
    if(humannum == 0 && ainum == 0)
        return 7;
    else if(humannum >= 1 && ainum >= 1)
        return 0;
    else if(c == H1_Player) {
        if(humannum == 1 && ainum == 0)
            return 35;
        else if(humannum == 2 && ainum == 0)
            return 800;
        else if(humannum == 3 && ainum == 0)
            return 15000;
        else if(humannum == 4 && ainum == 0)
            return 800000;
        else if(humannum == 0 && ainum == 1)
            return 15;
        else if(humannum == 0 && ainum == 2)
            return 400;
        else if(humannum == 0 && ainum == 3)
            return 1800;
        else
            return 100000;
    }
    else {
        if(humannum == 1 && ainum == 0)
            return 15;
        else if(humannum == 2 && ainum == 0)
            return 400;
        else if(humannum == 3 && ainum == 0)
            return 1800;
        else if(humannum == 4 && ainum == 0)
            return 100000;
        else if(humannum == 0 && ainum == 1)
            return 35;
        else if(humannum == 0 && ainum == 2)
            return 800;
        else if(humannum == 0 && ainum == 4)
            return 15000;
        else
            return 800000;
    }
}

//evaluate one position greedy
int GoBangAi::evaluateOnePos(int board[Grid_num][Grid_num], int row, int col, int c) {
    int res = 0;
    for(int d = 0; d < dir_num; d++) { // traverse the direction
        for(int i = 0; i < 5; i++) { // traverse the length
            Point st = getPoint(row, col, d, i - 4), ed = getPoint(st.y, st.x, d, 4);
            if(isInside(st.y, st.x) && isInside(ed.y, ed.x)) {
                //calculate the number of pieces respectively
                int humannum = 0, ainum = 0;
                for(int k = 0; k < 5; k++) {
                    Point temp = getPoint(st.y, st.x, d, k);
                    if(board[temp.y][temp.x] == H1_Player)
                        humannum++;
                    else if(board[temp.y][temp.x] == AI_Player)
                        ainum++;
                }
                //update the result
                res += gettuplescore(humannum, ainum, c);
            }
        }
    }
    return res;
}

Evaluation GoBangAi::evaluateBoard(int board[Grid_num][Grid_num]) {
    //init record array
    int state[dir_num][status_num];
    memset(state, 0, sizeof(state));
    int board_with_border[Grid_num + 2][Grid_num + 2];
    set_eval_board(board, board_with_border);

    //calculate the number of all types in 4 directions
    for (int d = 0; d < dir_num; d++) {
        int start_i, end_i, start_j, end_j;
        if (direction[d][0] == 0)
            start_i = 1, end_i = Grid_num;
        else
            start_i = 0, end_i = Grid_num - 4;
        if (direction[d][1] == 0)
            start_j = 1, end_j = Grid_num;
        else if (direction[d][1] == 1)
            start_j = 0, end_j = Grid_num - 4;
        else
            start_j = 5, end_j = Grid_num + 1;

        for (int i = start_i; i <= end_i; i++) {
            for (int j = start_j; j <= end_j; j++) {
                int type = tuple6type[board_with_border[i][j]][board_with_border[i + direction[d][0]][j + direction[d][1]]][board_with_border[i + 2 * direction[d][0]][j + 2 * direction[d][1]]][board_with_border[i + 3 * direction[d][0]][j + 3 * direction[d][1]]][board_with_border[i + 4 * direction[d][0]][j + 4 * direction[d][1]]][board_with_border[i + 5 * direction[d][0]][j + 5 * direction[d][1]]];
                state[d][type]++;
            }
        }
    }

    //calculate the score and record special states
    Evaluation res;
    memset(res.state, 0, sizeof(res.state));

    int score = 0;
    for (int i = 1; i < status_num; i++) {
        int count = 0;
        for (int d = 0; d < dir_num; d++) {
            score += state[d][i] * weight[i];
            count += state[d][i];
        }
        if (i == ai_win)
            res.state[ai_win] = count;
        else if (i == ai_lose)
            res.state[ai_lose] = count;
        else if (i == ai_flex4)
            res.state[ai_flex4] = count;
        else if (i == ai_block4)
            res.state[ai_block4] = count;
        else if (i == ai_flex3)
            res.state[ai_flex3] = count;
    }

    res.result = result_draw;
    if (res.state[ai_win] > 0)
        res.result = result_ai_win;
    else if (res.state[ai_lose] > 0)
        res.result = result_human_win;

    res.score = score;

    return res;
}
/*------------------------------evaluate-----------------------------------*/

/*--------------------------------search-----------------------------------*/
Points GoBangAi::seekPoints(int board[Grid_num][Grid_num]) {
    Points points;
    bool vis[Grid_num][Grid_num];
    int worth[Grid_num][Grid_num];
    memset(vis, 0, sizeof(vis));
    const int search_depth = 3;

    for (int i = 0; i < Grid_num; i++)
        for (int j = 0; j < Grid_num; j++)
            if(board[i][j] != No_Player)
                for (int k = -search_depth; k <= search_depth; k++)
                    for (int d = 0; d < 4; d++)
                        if (isInside(i + k * direction[d][0], j + k * direction[d][1]))
                            vis[i + k * direction[d][0]][j + k * direction[d][1]] = true;

    for (int i = 0; i < Grid_num; i++) {
        for (int j = 0; j < Grid_num; j++) {
            worth[i][j] = -INT_MAX;
            if(board[i][j] == No_Player && vis[i][j] == true)
                worth[i][j] = evaluateOnePos(board, i, j, AI_Player);
        }
    }

    int w;
    for (int k = 0; k < Point_num; k++) {
        w = -INT_MAX;
        for (int i = 0; i < Grid_num; i++) {
            for (int j = 0; j < Grid_num; j++) {
                if (worth[i][j] > w) {
                    w = worth[i][j];
                    Point temp(j, i);
                    points.point[k] = temp;
                }
            }
        }

        int x = points.point[k].x, y = points.point[k].y;
        //qDebug() << x << " " << y << endl;
        board[y][x] = AI_Player;
        points.score[k] = evaluateBoard(board).score;
        board[y][x] = No_Player;

        worth[y][x] = -INT_MAX;
    }
    return points;
}

void GoBangAi::copyBoard(int source[Grid_num][Grid_num], int board[Grid_num][Grid_num]) {
    for (int i = 0; i < Grid_num; i++)
        for (int j = 0; j < Grid_num; j++)
            board[i][j] = source[i][j];
}

void GoBangAi::reverseBoard(int source[Grid_num][Grid_num], int board[Grid_num][Grid_num]) {
    for (int i = 0; i < Grid_num; i++) {
        for (int j = 0; j < Grid_num; j++) {
            if (source[i][j] == H1_Player)
                board[i][j] = AI_Player;
            else if (source[i][j] == AI_Player)
                board[i][j] = H1_Player;
            else
                board[i][j] = No_Player;
        }
    }
}

int GoBangAi::MinMax_Search_with_Purning(int board[Grid_num][Grid_num], int depth, int alpha, int beta) {
    Evaluation eval = evaluateBoard(board);
    if (depth == 0 || eval.result != result_draw) { // reach the max depth or find a kill result
        if (depth == 0) {
            Points p = seekPoints(board);
            return p.score[0];
        }
        else
            return eval.score;
    }
    else if (depth % 2 == 0) { // max ai
        Points p = seekPoints(board);
        for (int i = 0; i < 10; i++) {
            int copyboard[Grid_num][Grid_num];
            copyBoard(board, copyboard);
            copyboard[p.point[i].y][p.point[i].x] = AI_Player;
            int a = MinMax_Search_with_Purning(copyboard, depth - 1, alpha, beta);
            if (a > alpha) {
                alpha = a;
                if (depth == 6) {
                    select_point = p.point[i];
                    select_point_score = a;
                }
            }
            //purning
            if (beta <= alpha)
                break;
        }
        return alpha;
    }
    else { // min human
        int reverseboard[Grid_num][Grid_num];
        reverseBoard(board, reverseboard);
        Points p = seekPoints(reverseboard);
        for (int i = 0; i < 10; i++) {
            int copyboard[Grid_num][Grid_num];
            copyBoard(board, copyboard);
            copyboard[p.point[i].y][p.point[i].x] = H1_Player;
            int a = MinMax_Search_with_Purning(copyboard, depth - 1, alpha, beta);
            if (a < beta)
                beta = a;
            //purning
            if (beta <= alpha)
                break;
        }
        return beta;
    }
}

QList<Point> GoBangAi::seek_kill_points(int board[Grid_num][Grid_num]) {
    QList<Point> pointlist;
    Points p = seekPoints(board);
    int copyboard[Grid_num][Grid_num];
    copyBoard(board, copyboard);
    for(int i = 0; i < Point_num; i++) {
        copyboard[p.point[i].y][p.point[i].x] = AI_Player;
        Evaluation a = evaluateBoard(copyboard), b = evaluateBoard(board);
        if(a.state[ai_win] > 0)
            pointlist.append(p.point[i]);
        else if(a.state[ai_flex4] > b.state[ai_flex4])
            pointlist.append(p.point[i]);
        else if(a.state[ai_block4] > b.state[ai_block4])
            pointlist.append(p.point[i]);
        else if(a.state[ai_flex3] > b.state[ai_flex3])
            pointlist.append(p.point[i]);
        copyboard[p.point[i].y][p.point[i].x] = No_Player;
    }
    return pointlist;
}

bool GoBangAi::find_kill(int board[Grid_num][Grid_num], int depth) {
    Evaluation eval = evaluateBoard(board);
    if(depth == 0 || eval.result != result_draw) {
        if(depth == 0) {
            Points p = seekPoints(board);
            board[p.point[0].y][p.point[0].x] = AI_Player;
            GameResult result = evaluateBoard(board).result;
            if(result == result_ai_win)
                return true;
            else
                return false;
        }
        else if(eval.result == result_ai_win)
            return true;
        else
            return false;
    }
    else if(depth % 2 == 0) {
        if(depth == 16 || depth == 14) {
            Points p = seekPoints(board);
            for(int i = 0; i < 10; i++) {
                int copyboard[Grid_num][Grid_num];
                copyBoard(board, copyboard);
                copyboard[p.point[i].y][p.point[i].x] = AI_Player;
                if(find_kill(copyboard, depth - 1)) {
                    if(depth == 16)
                        select_point = p.point[i];
                    return true;
                }
            }
            return false;
        }
        else {
            QList<Point> pointlist = seek_kill_points(board);
            if(pointlist.length() == 0)
                return false;
            for(auto i : pointlist) {
                int copyboard[Grid_num][Grid_num];
                copyBoard(board, copyboard);
                copyboard[i.y][i.x] = AI_Player;
                if(find_kill(copyboard, depth - 1))
                    return true;
            }
            return false;
        }
    }
    else {
        int reverseboard[Grid_num][Grid_num];
        reverseBoard(board, reverseboard);
        Points p = seekPoints(reverseboard);
        int copyboard[Grid_num][Grid_num];
        copyBoard(board, reverseboard);
        copyboard[p.point[0].y][p.point[0].x] = H1_Player;
        return find_kill(copyboard, depth - 1);
    }
}

Point GoBangAi::ai_run() {
    if(gobang_cnt == 0)
        return {Grid_num / 2, Grid_num / 2};
    //if(!find_kill(GoBangboard, 16))
    MinMax_Search_with_Purning(GoBangboard, 6, -INT_MAX, INT_MAX);
    return select_point;
}
/*--------------------------------search-----------------------------------*/
