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
INCLUDEPATH += $$PWD/headers/

SOURCES += src/main.cpp \
    src/qanda.cpp \
    src/instrument.cpp

HEADERS += \
    headers/qanda.h \
    headers/instrument.h

DISTFILES += \
    resources/api_key.txt \
    .gitignore
