#-------------------------------------------------
#
# Project created by QtCreator 2016-04-15T13:47:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport multimedia

TARGET = ACBC
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++1y

SOURCES += main.cpp\
        acbcgui.cpp \
    LED/qledindicator.cpp \
    Alix/alixcom.cpp \
    Error/ACBCError.cpp \
    log/Logger.cpp \
    pugi/pugixml.cpp \
    Socket/TCPAcceptor.cpp \
    Socket/TCPConnector.cpp \
    Socket/TCPStream.cpp \
    Socket/TuxServer.cpp \
    core.cpp \
    qcustomplot/qcustomplot.cpp \
    Tempgraph/tempplot.cpp \
    Tempgraph/pressureplot.cpp \
    log/logfile.cpp \
    Dialogs/dialogaus.cpp \
    Dialogs/dialogprint.cpp \
    PID/pid.cpp \
    Dialogs/acbcaudio.cpp

HEADERS  += acbcgui.h \
    LED/qledindicator.h \
    Alix/alixcom.h \
    datastructs/states.h \
    datastructs/structs.h \
    Error/ACBCError.h \
    log/Logger.h \
    pugi/pugiconfig.hpp \
    pugi/pugixml.hpp \
    Socket/TCPAcceptor.h \
    Socket/TCPConnector.h \
    Socket/TCPStream.h \
    Socket/TuxServer.h \
    core.h \
    qcustomplot/qcustomplot.h \
    Tempgraph/tempplot.h \
    Tempgraph/pressureplot.h \
    log/logfile.h \
    Dialogs/dialogaus.h \
    Dialogs/dialogprint.h \
    PID/pid.h \
    Dialogs/acbcaudio.h

FORMS    += acbcgui.ui \
    Tempgraph/tempplot.ui \
    Tempgraph/pressureplot.ui \
    Dialogs/dialogaus.ui \
    Dialogs/dialogprint.ui
