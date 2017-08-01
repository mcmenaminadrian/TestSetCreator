#-------------------------------------------------
#
# Project created by QtCreator 2017-07-29T22:30:52
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11
LIBS += -ljpeg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestSetCreator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    masterjpeg.cpp \
    picturedisplay.cpp

HEADERS  += mainwindow.h \
    masterjpeg.hpp \
    picturedisplay.hpp

FORMS    += mainwindow.ui
