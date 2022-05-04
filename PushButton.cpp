#include "PushButton.h"
#include <QPropertyAnimation>

PushButton::PushButton(QWidget *parent) : QPushButton(parent) {

}

void PushButton::closeEvent(QEvent* event) {
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(3000);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    event->accept();
}
