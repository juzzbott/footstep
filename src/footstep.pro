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
    app/about.cpp \
    app/controls/maplayer.cpp \
    core/geopoint.cpp \
    app/controls/geolayer.cpp

HEADERS  += app/mainwindow.h \
    app/about.h \
    app/controls/maplayer.h \
    core/geopoint.h \
    app/controls/geolayer.h

FORMS    += ui/mainwindow.ui \
    ui/about.ui
