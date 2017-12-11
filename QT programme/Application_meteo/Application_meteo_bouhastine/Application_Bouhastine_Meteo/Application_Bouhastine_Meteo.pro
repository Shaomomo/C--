#-------------------------------------------------
#
# Project created by QtCreator 2016-10-19T14:21:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Application_Bouhastine_Meteo
TEMPLATE = app


SOURCES +=\
        dialog.cpp \
    clienthttp.cpp \
    main.cpp \
    requetewu.cpp \
    meteowu.cpp \
    threadmeteowu.cpp

HEADERS  += dialog.h \
    clienthttp.h \
    meteowu.h \
    requetewu.h \
    threadmeteowu.h

FORMS    += dialog.ui
win32:LIBS += C:\Qt\Qt5.3.2\Tools\mingw482_32\i686-w64-mingw32\lib\libws2_32.a
