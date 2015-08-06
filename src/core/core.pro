#-------------------------------------------------
#
# Project created by QtCreator 2015-07-23T08:14:06
#
#-------------------------------------------------

include(../../defaults.pri)
QT       += core
QT       -= gui

TARGET = core
TEMPLATE = lib


SOURCES += geopoint.cpp \
    json/json.cpp \
    config/footstepconfigloader.cpp \
    config/footstepconfig.cpp

HEADERS  += geopoint.h \
    json/json.h \
	constants.h \
    config/footstepconfigloader.h \
    config/footstepconfig.h \
    json/ijsonserializable.h

#debug:   DESTDIR  = build/core/debug
#release: DESTDIR  = build/core/release
