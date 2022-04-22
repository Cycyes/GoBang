#ifndef BASE_H
#define BASE_H

#include <QDebug>

enum Game_Flag {
    init_flag = -1
};

enum Game_Mode {
    PVE,
    PVP
};

enum Game_Player {
    No_Player,
    AI_Player,
    H1_Player,
    H2_Player,
    Out_Player
};

enum Window_SIZE {
    Window_Width = 790,
    Window_Height = (int)(Window_Width * 1.082)
};

enum Chess_Piece_SIZE {
    Chess_Piece_Radius = 14
};

enum Grid_SIZE {
    Grid_Width = 40,
    Grid_num = 15,
    Mark_Radius = 2,
    Detect_Radius = Grid_Width / 2 - 2
};

enum Board_SIZE {
    Board_Width = (Grid_num - 1) * Grid_Width,
    Board_start_X = (Window_Width - Board_Width) / 2,
    Board_end_X = Board_start_X + Board_Width,
    Board_start_Y = Board_start_X,
    Board_end_Y = Board_end_X
};

enum Button_Menu {
    Min_Button,
    Close_Button,
    Button_Menu_num
};

enum Button_Ctrl {
    New_Button,
    Mode_Button,
    Change_Button,
    Retract_Button,
    Button_Ctrl_num
};

enum Button_Ctrl_Pos {
    Button_Ctrl_Width = 86,
    Button_Ctrl_Height = 36,
    Button_Ctrl_start_X = Board_start_X + Button_Ctrl_Height / 4 + 3,
    Button_Ctrl_end_X = Board_end_X - Button_Ctrl_Width - Button_Ctrl_Height / 4 - 3,
    Button_Ctrl_start_Y = Board_end_Y + Button_Ctrl_Height * 6/5,
    Button_Ctrl_D = (Button_Ctrl_end_X - Button_Ctrl_start_X) / (Button_Ctrl_num - 1)
};

enum Button_Menu_Pos {
    Button_Menu_Width = 30,
    Button_Menu_Height = 30,
    Button_Menu_D = 32,
    Button_Menu_start_X = Window_Width - Button_Menu_num * (int)(Button_Menu_D * 1.15),
    Button_Menu_start_Y = Button_Menu_Height / 4,
    Button_Menu_end_Y = Button_Menu_Height + Button_Menu_start_Y
};

const int position_value[Grid_num][Grid_num] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0},
    {0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 0},
    {0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1, 0},
    {0, 1, 2, 3, 4, 5, 5, 5, 5, 5, 4, 3, 2, 1, 0},
    {0, 1, 2, 3, 4, 5, 6, 6, 6, 5, 4, 3, 2, 1, 0},
    {0, 1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1, 0},
    {0, 1, 2, 3, 4, 5, 6, 6, 6, 5, 4, 3, 2, 1, 0},
    {0, 1, 2, 3, 4, 5, 5, 5, 5, 5, 4, 3, 2, 1, 0},
    {0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1, 0},
    {0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 0},
    {0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

const int direction[4][2] = {
    {1, 0},
    {0, 1},
    {1, 1},
    {1, -1}
};

const int Negative_Infinity = -0x3f3f3f3f;

#endif // BASE_H
