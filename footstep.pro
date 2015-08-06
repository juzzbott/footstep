#-------------------------------------------------
#
# Project created by QtCreator 2015-07-23T08:14:06
#
#-------------------------------------------------

CONFIG       += ordered

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = subdirs

SUBDIRS = \
	src/core \
	src/app
    
app.depends = core
