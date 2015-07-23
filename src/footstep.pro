#-------------------------------------------------
#
# Project created by QtCreator 2015-07-23T08:14:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = footstep
TEMPLATE = app


SOURCES += main.cpp\
        app/mainwindow.cpp \
    model/track.cpp

HEADERS  += app/mainwindow.h \
    model/track.h

FORMS    += ui/mainwindow.ui
