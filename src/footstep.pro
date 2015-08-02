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
	app/preferences.cpp \
    core/geopoint.cpp \
    app/controls/geolayer.cpp \
    app/controls/mapscene.cpp \
    app/controls/mapview.cpp \
    app/controls/layerobject.cpp \
    app/controls/internal/internalgraphicsscene.cpp \
    app/controls/internal/internalgraphicsview.cpp \
    app/controls/tilesources/maptilesource.cpp \
	app/controls/mapgraphics/mapgraphicsobject.cpp \
    lib/json.cpp \
    config/footstepconfigloader.cpp \
    config/footstepconfig.cpp

HEADERS  += app/mainwindow.h \
	app/about.h \
	app/preferences.h \
    core/geopoint.h \
    app/controls/geolayer.h \
    app/controls/mapscene.h \
    app/controls/mapview.h \
    app/controls/layerobject.h \
    app/controls/internal/internalgraphicsscene.h \
    app/controls/internal/internalgraphicsview.h \
    app/controls/tilesources/maptilesource.h \
	app/controls/mapgraphics/mapgraphicsobject.h \
    lib/json.h \
    core/constants.h \
    config/footstepconfigloader.h \
    config/footstepconfig.h

FORMS    += ui/mainwindow.ui \
    ui/about.ui \
    ui/preferences.ui
