#-------------------------------------------------
#
# Project created by QtCreator 2014-07-15T19:38:24
#
#-------------------------------------------------

QT       += core gui widgets webchannel websockets



TARGET = VideoPlayer
TEMPLATE = app


SOURCES += main.cpp\
    videoplayer.cpp \
    copyprocessor.cpp \
    shared/websocketclientwrapper.cpp \
    shared/websockettransport.cpp \
    jsontransmitter.cpp

HEADERS  += videoplayer.h \
    copyprocessor.h \
    shared/websocketclientwrapper.h \
    shared/websockettransport.h \
    jsontransmitter.h

FORMS    += videoplayer.ui

include(../opencv/videoengine.pri)
