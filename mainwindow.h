#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

#include "GoBangBoard.h"
#include "base.h"
#include "Point.h"
#include "PushButton.h"
#include "GoBangAi.h"
#include "DrawPainter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //init
    void initWindow();
    void initButton();
    void initConnections();

    //game
    void startPVEGame();
    void startPVPGame();
    void resetPVEGame();
    void resetPVPGame();
    void retractPVEGame();
    void retractPVPGame();
    void PVERound();
    void PVPRound();
    void PVEPutPiece(const Point &next_move, const int id);
    void PVPPutPiece(const Point &next_move, const int id);
    void aiMove(const Point& next_move);

private:
    Ui::MainWindow *ui;

    char game_mode;
    int now_player_id;
    int black_player_id;
    GoBangBoard gobang_board;

    Point mouse_cursor;
    Point record_moves[Grid_num * Grid_num];
    int gobang_cnt;

    GoBangAi ai;

    PushButton button_ctrl[Button_Ctrl_num];
    PushButton button_menu[Button_Menu_num];
    QLabel message_text[3];

    int Distance(int x0, int y0, int x1, int y1);
    void findNearPos(const Point & near_pos, int x, int y);

    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void closeEvent(QCloseEvent *event);
};
#endif // MAINWINDOW_H
