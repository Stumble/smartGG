#-------------------------------------------------
#
# Project created by QtCreator 2016-07-21T07:10:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HomeDefender
TEMPLATE = app

LIBS += -lcurl

SOURCES += main.cpp\
        mainwindow.cpp \
    SPort.cpp \
    DataDecoder.cpp \
    chttpp.cpp

HEADERS  += mainwindow.h \
    SPort.h \
    DataDecoder.h \
    callpy.h \
    chttpp.h
    
FORMS    += mainwindow.ui
