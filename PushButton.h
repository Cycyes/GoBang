#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QPushButton>
#include <QCloseEvent>

class PushButton : public QPushButton {
public:
    PushButton(QWidget *parent = Q_NULLPTR);
    virtual void closeEvent(QEvent* event);
    void test();
};

#endif // PUSHBUTTON_H
