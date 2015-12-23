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
    src/instrument.cpp \
    src/interfacer.cpp \
    src/account.cpp \
    src/qblocker.cpp \
    src/qmarkedreply.cpp

HEADERS += \
    headers/instrument.h \
    headers/interfacer.h \
    headers/account.h \
    headers/qblocker.h \
    headers/qmarkedreply.h

DISTFILES += \
    resources/api_key.txt \
    .gitignore \
    NOTES.txt
