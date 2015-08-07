#-------------------------------------------------
#
# Project created by QtCreator 2015-07-23T08:14:06
#
#-------------------------------------------------

include(../../defaults.pri)
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = footstep
TEMPLATE = app
INCLUDEPATH = ../


SOURCES += main.cpp\
		mainwindow.cpp \
	about.cpp \
	preferences.cpp \
	controls/geolayer.cpp \
	controls/mapscene.cpp \
	controls/mapview.cpp \
	controls/layerobject.cpp \
	controls/internal/internalgraphicsscene.cpp \
	controls/internal/internalgraphicsview.cpp \
	controls/tilesources/maptilesource.cpp \
	controls/mapgraphics/mapgraphicsobject.cpp \
    controls/internal/internalgraphicsobject.cpp

HEADERS  += mainwindow.h \
	about.h \
	preferences.h \
	controls/geolayer.h \
	controls/mapscene.h \
	controls/mapview.h \
	controls/layerobject.h \
	controls/internal/internalgraphicsscene.h \
	controls/internal/internalgraphicsview.h \
	controls/tilesources/maptilesource.h \
	controls/mapgraphics/mapgraphicsobject.h \
    controls/internal/internalgraphicsobject.h

FORMS    += ../ui/mainwindow.ui \
    ../ui/about.ui \
    ../ui/preferences.ui

LIBS += -L../core/debug/ -lcore
