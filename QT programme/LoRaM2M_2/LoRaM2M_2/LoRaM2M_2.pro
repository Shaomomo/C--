#-------------------------------------------------
#
# Project created by QtCreator 2017-04-21T15:14:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LoRaM2M_2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    LoraM2M.cpp

HEADERS  += mainwindow.h \
    PortComDI.h \
    LoraM2M.h

FORMS    += mainwindow.ui
