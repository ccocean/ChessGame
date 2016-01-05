#-------------------------------------------------
#
# Project created by QtCreator 2016-01-04T14:10:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChessGame
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    chess.cpp

HEADERS  += mainwindow.h \
    chess.h

FORMS    += mainwindow.ui

INCLUDEPATH+=include\
INCLUDEPATH+=include\opencv\
INCLUDEPATH+=include\opencv2\

LIBS+=-L$$PWD/lib





