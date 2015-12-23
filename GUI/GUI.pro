#-------------------------------------------------
#
# Project created by QtCreator 2015-12-12T18:06:58
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI
TEMPLATE = app
INCLUDEPATH += $$PWD/../headers/

SOURCES += main.cpp\
        mainwindow.cpp \
    accountinfo.cpp

SOURCES += ../src/main.cpp \
    ../src/instrument.cpp \
    ../src/interfacer.cpp \
    ../src/account.cpp \
    ../src/qblocker.cpp \
    ../src/qmarkedreply.cpp

HEADERS  += mainwindow.h \
    accountinfo.h


HEADERS += \
    ../headers/instrument.h \
    ../headers/interfacer.h \
    ../headers/account.h \
    ../headers/qblocker.h \
    ../headers/qmarkedreply.h

FORMS    += mainwindow.ui \
    accountinfo.ui
