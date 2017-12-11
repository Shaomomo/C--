#-------------------------------------------------
#
# Project created by QtCreator 2017-03-24T16:35:56
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LoraKit2
TEMPLATE = app


SOURCES += main.cpp\
        lorakit.cpp \
    SNIRconversions.cpp

HEADERS  += lorakit.h \
    SNIRconversions.h

FORMS    += lorakit.ui
