#-------------------------------------------------
#
# Project created by QtCreator 2011-01-22T17:41:15
#
#-------------------------------------------------

QT       += core network script

QT       -= gui

TARGET = GowallaApi
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    api/gowallaapi.cpp \
    api/user.cpp \
    api/spot.cpp \
    api/activity.cpp

HEADERS += \
    api/gowallaapi.h \
    api/user.h \
    api/spot.h \
    api/activity.h
