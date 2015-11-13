#-------------------------------------------------
#
# Project created by QtCreator 2015-11-13T08:53:22
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = Qanda
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    qanda.cpp \
    instrument.cpp

HEADERS += \
    qanda.h \
    instrument.h

DISTFILES += \
    api_key.txt \
    .gitignore
