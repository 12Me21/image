TEMPLATE = app
TARGET = a.out

SOURCES += main.cpp
QT += core widgets
LIBS += -llua5.3

INCLUDEPATH += .
PRECOMPILED_HEADER = precompile.h
CONFIG += precompile_header
