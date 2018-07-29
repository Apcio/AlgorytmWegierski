TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Program.cpp \
    Algorithm.cpp \
    Matrix.cpp

HEADERS += \
    Program.h \
    Algorithm.h \
    Matrix.h \
    Cell.h

QMAKE_CXXFLAGS = -std=c++11
