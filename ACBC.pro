#-------------------------------------------------
#
# Project created by QtCreator 2016-04-15T13:47:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ACBC
TEMPLATE = app


SOURCES += main.cpp\
        acbcgui.cpp \
    LED/qledindicator.cpp

HEADERS  += acbcgui.h \
    LED/qledindicator.h

FORMS    += acbcgui.ui
