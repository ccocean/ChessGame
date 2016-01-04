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
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH+=C:\OpenCV\install\include\
INCLUDEPATH+=C:\OpenCV\install\include\opencv\
INCLUDEPATH+=C:\OpenCV\install\include\opencv2\

LIBS+=-LC:\OpenCV\install\x86\vc12\lib\

