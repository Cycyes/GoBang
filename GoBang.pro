QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DrawPainter.cpp \
    GoBangAi.cpp \
    GoBangBoard.cpp \
    Point.cpp \
    PushButton.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    DrawPainter.h \
    GoBangAi.h \
    GoBangBoard.h \
    Point.h \
    PushButton.h \
    base.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    GoBang_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
