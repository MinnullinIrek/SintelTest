TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    board.cpp \
    cell.cpp \
    knight.cpp \
    mover.cpp \
    visualizer.cpp \
    visualchar.cpp

HEADERS += \
    board.h \
    cell.h \
    knight.h \
    mover.h \
    visualizer.h \
    visualchar.h
