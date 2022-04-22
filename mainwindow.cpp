#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "base.h"
#include "DrawPainter.h"
#include "GoBangBoard.h"
#include "ai.h"

#include <QPropertyAnimation>
#include <QMessageBox>
#include <QEvent>
#include <qt_windows.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , game_mode(PVP)
    , black_player_id(H1_Player)
{
    qRegisterMetaType<BoardPosition>("BoardPosition");
    this->initWindow();
    this->initButton();
    this->initConnections();

    if(game_mode == PVE) {
        this->resetPVEGame();
        this->startPVEGame();
    }
    else if(game_mode == PVP) {
        this->resetPVPGame();
        this->startPVPGame();
    }
}

MainWindow::~MainWindow()
{

}

/*----------------------------------------init---------------------------------*/
void MainWindow::initWindow() {
    //set font
    QFont font("Century Gothic", 8);
    QApplication::setFont(font);

    //set Window
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    this->setFixedSize(Window_Width, Window_Height);
    this->setWindowTitle(QString("人工智能带带我"));
    this->move(Window_Width / 2, Window_Height / 8);
    this->setMouseTracking(true);

    //set animation
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(250);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
}

void MainWindow::initButton() {
    //init button
    for(int i = 0; i < Button_Ctrl_num; i++) {
        button_ctrl[i].setParent(this);
        button_ctrl[i].setGeometry(Button_Ctrl_start_X + i * Button_Ctrl_D, Button_Ctrl_start_Y, Button_Ctrl_Width, Button_Ctrl_Height);
        //button_ctrl[i].setStyleSheet(Butt)
    }
    for(int i = 0; i < Button_Menu_num; i++) {
        button_menu[i].setParent(this);
        button_menu[i].setGeometry(Button_Menu_start_X + i * Button_Menu_D, Button_Menu_start_Y, Button_Menu_Width, Button_Menu_Height);
        //button_menu[i].set
    }

    //set button content
    button_menu[Min_Button].setText("-");
    button_menu[Close_Button].setText("x");
    button_ctrl[New_Button].setText("New");
    button_ctrl[Mode_Button].setText("Mode");
    button_ctrl[Change_Button].setText("Change");
    button_ctrl[Retract_Button].setText("Retract");
}

void MainWindow::initConnections() {
    //

    //set connections of menu buttons
    connect(button_menu + Min_Button, &PushButton::clicked, this, &MainWindow::showMinimized);
    connect(button_menu + Close_Button, &PushButton::clicked, this, &MainWindow::close);

    //set connections of ctrl buttons
    connect(button_ctrl + New_Button, &PushButton::clicked,
            [&]() {
        if(game_mode == PVE) {
            if(now_player_id != AI_Player) {
                this->resetPVEGame();
                this->startPVEGame();
            }
        }
        else if(game_mode == PVP) {
            this->resetPVPGame();
            this->startPVPGame();
        }
    });
    connect(button_ctrl + Mode_Button, &PushButton::clicked,
            [&]() {
        if(now_player_id != AI_Player) {
            if(game_mode == PVE) {
                game_mode = PVP;
                black_player_id = H1_Player;
                this->resetPVPGame();
                this->startPVPGame();
            }
            else if(game_mode == PVP) {
                game_mode = PVE;
                black_player_id = AI_Player;
                this->resetPVEGame();
                this->startPVEGame();
            }
        }

    });
    connect(button_ctrl + Change_Button, &PushButton::clicked,
            [&]() {
        if(game_mode == PVE) {
            if(now_player_id == H1_Player) {
                if(black_player_id == AI_Player)
                    black_player_id = H1_Player;
                else
                    black_player_id = AI_Player;
                this->resetPVEGame();
                this->startPVEGame();
            }
        }
        else if(game_mode == PVP) {
            this->resetPVPGame();
            this->startPVPGame();
        }
    });
    connect(button_ctrl + Retract_Button, &PushButton::clicked,
            [&]() {
        if(game_mode == PVE) {
            if(now_player_id != AI_Player)
                this->retractPVEGame();
        }
        else if(game_mode == PVP) {
            this->retractPVPGame();
        }
    });
}
/*----------------------------------------init---------------------------------*/

/*----------------------------------------game---------------------------------*/
void MainWindow::startPVEGame() {
    now_player_id = black_player_id;
    gobang_board.setBlackPlayerID(black_player_id);
    if(black_player_id == AI_Player) {
        ai.set_id(true);
        const BoardPosition &next_move = ai.ai_run();
        this->aiMove(next_move);
    }
    else if(black_player_id == H1_Player)
        ai.set_id(false);
}

void MainWindow::startPVPGame() {
    now_player_id = black_player_id;
    gobang_board.setBlackPlayerID(black_player_id);
}

void MainWindow::resetPVEGame() {
    gobang_cnt = 0;
    mouse_cursor = {init_flag, init_flag};
    gobang_board.initboard();
    ai.initboard();
    ai.set_depth(3);
    ai.set_cnt(0);
    this->update();
}

void MainWindow::resetPVPGame() {
    gobang_cnt = 0;
    mouse_cursor.x = mouse_cursor.y = init_flag;
    gobang_board.initboard();
    ai.initboard();
    this->update();
}

void MainWindow::retractPVEGame() {
    if(gobang_cnt >= 3) {
        const BoardPosition& last_human_move = record_moves[gobang_cnt - 2];
        const BoardPosition& last_ai_move = record_moves[gobang_cnt - 1];
        ai.takePiece(last_human_move.x, last_human_move.y);
        ai.takePiece(last_ai_move.x, last_ai_move.y);
        gobang_board.takePiece(last_human_move.x, last_human_move.y);
        gobang_board.takePiece(last_ai_move.x, last_ai_move.y);
        this->update();
        gobang_cnt -= 2;
        ai.set_cnt(gobang_cnt);
    }
    else {
        this->resetPVEGame();
        this->startPVEGame();
    }
}

void MainWindow::retractPVPGame() {
    if(gobang_cnt > 2) {
        const BoardPosition& last_H1_player_move = record_moves[gobang_cnt - 2];
        const BoardPosition& last_H2_player_move = record_moves[gobang_cnt - 1];
        gobang_board.takePiece(last_H1_player_move.x, last_H1_player_move.y);
        gobang_board.takePiece(last_H2_player_move.x, last_H2_player_move.y);
        gobang_cnt -= 2;
        this->update();
    }
    else {
        this->resetPVPGame();
        this->startPVPGame();
    }
}

void MainWindow::PVERound() {
    this->PVEPutPiece(mouse_cursor, H1_Player);
    this->update();
    if(gobang_board.win(mouse_cursor, H1_Player)) {
        QMessageBox::information(this, "", "玩家胜利！");
        this->resetPVEGame();
        this->startPVEGame();
    }
    else {
        now_player_id = AI_Player;
        const BoardPosition &next_move = ai.ai_run();
        this->aiMove(next_move);
    }
}

void MainWindow::PVPRound() {
    this->PVPPutPiece(mouse_cursor, now_player_id);
    this->update();
    if(now_player_id == H1_Player) {
        if(gobang_board.win(mouse_cursor, now_player_id)) {
            QMessageBox::information(this, "", "黑子赢");
            this->resetPVPGame();
            this->startPVPGame();
        }
        else
            now_player_id = H2_Player;
    }
    else if(now_player_id == H2_Player) {
        if(gobang_board.win(mouse_cursor, now_player_id)) {
            QMessageBox::information(this, "", "白子赢");
            this->resetPVPGame();
            this->startPVPGame();
        }
        else
            now_player_id = H1_Player;
    }
}

void MainWindow::PVEPutPiece(const BoardPosition &next_move, const int id) {
    if(gobang_board.isAvaliable(next_move)) {
        gobang_board.putPiece(next_move.x, next_move.y, id);
        ai.putPiece(next_move.x, next_move.y, id);
        record_moves[gobang_cnt++] = next_move;
        ai.set_cnt(gobang_cnt);
    }
}

void MainWindow::PVPPutPiece(const BoardPosition &next_move, const int id) {
    if(gobang_board.isAvaliable(next_move)) {
        gobang_board.putPiece(next_move.x, next_move.y, id);
        record_moves[gobang_cnt++] = next_move;
    }
}

void MainWindow::aiMove(const BoardPosition& next_move) {
    this->PVEPutPiece(next_move, AI_Player);
    this->update();
    if(gobang_board.win(next_move, AI_Player)) {
        QMessageBox::information(this, "", "AI胜利啦！");
        this->resetPVEGame();
        this->startPVEGame();
    }
    else
        now_player_id = H1_Player;
}
/*----------------------------------------game---------------------------------*/

/*-----------------------------------------ui----------------------------------*/
void MainWindow::paintEvent(QPaintEvent *event) {
    DrawPainter painter(this);
    painter.init();
    painter.DrawBoard();

    if(gobang_board.isAvaliable(mouse_cursor) && now_player_id != AI_Player)
        painter.DrawMark();

    //draw all chess pieces
    painter.DrawChessPieces(gobang_board);

    //draw last move
    if(gobang_cnt && gobang_board.isInside(record_moves[gobang_cnt - 1]))
        painter.DrawLastMove(record_moves[gobang_cnt - 1], now_player_id == black_player_id);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    int x = event->x(), y = event->y();
    if(x >= Board_start_X && x <= Board_end_X && y >= Board_start_Y && y <= Board_end_Y) {
        BoardPosition near_pos((x - Board_start_X) / Grid_Width, (y - Board_start_Y) / Grid_Width);
        this->findNearPos(near_pos, x, y);
        this->update();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    if(game_mode == PVE && gobang_board.isAvaliable(mouse_cursor) && this->now_player_id == H1_Player)
        PVERound();
    else if(game_mode == PVP && gobang_board.isAvaliable(mouse_cursor))
        PVPRound();
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if(ReleaseCapture() && event->y() <= Button_Menu_D) {
        QWidget *pWindow = this->window();
        if(pWindow->isTopLevel())
            SendMessage(HWND(pWindow->winId()),WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {

}
/*-----------------------------------------ui----------------------------------*/

/*-------------------------------------ui-function-----------------------------*/
int MainWindow::Distance(int x0, int y0, int x1, int y1) {
    int dx = x0 - x1, dy = y0 -y1;
    return (int)sqrt(dx * dx + dy * dy);
}

void MainWindow::findNearPos(const BoardPosition &near_pos, int x, int y) {
    const int dx[] = {0, 1, 0, 1};
    const int dy[] = {0, 0, 1, 1};
    int x0 = Board_start_X + Grid_Width * near_pos.x, y0 = Board_start_Y + Grid_Width * near_pos.y;

    mouse_cursor.x = mouse_cursor.y = init_flag;

    int min_dis = Window_Height * Window_Height;
    for(int i = 0; i < 4; i++) {
        int xi = x0 + dx[i] * Grid_Width, yi = y0 + dy[i] * Grid_Width;
        int now_dis = Distance(x, y, xi, yi);
        if(Detect_Radius >= now_dis && min_dis > now_dis) {
            mouse_cursor.x = near_pos.x + dx[i] - 1;
            mouse_cursor.y = near_pos.y + dy[i] - 1;
            min_dis = now_dis;
        }
    }
}
/*-------------------------------------ui-function-----------------------------*/
