TEMPLATE = app
TARGET = "Animal Abuse"

QT = core gui

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

SOURCES += \
    button.cpp \
    game.cpp \
    gui.cpp \
    main.cpp \
    player.cpp \
    unit.cpp

HEADERS += \
    button.h \
    game.h \
    gui.h \
    player.h \
    unit.h

RESOURCES += \
    rsc.qrc

DISTFILES +=
