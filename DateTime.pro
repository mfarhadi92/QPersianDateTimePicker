#-------------------------------------------------
#
# Project created by QtCreator 2018-07-10T14:43:27
# Mehdi farhadi
# mfarhadi.ece.iut.ac.ir
# 09134223351
# mfarhadiir@gmail.com
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DateTime
CONFIG += c++11
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qpersiandatetime.cpp \
    qpersiandatetimeinput.cpp \
    qpersiandatetimewidget.cpp

HEADERS  += mainwindow.h \
    qpersiandatetime.h \
    qpersiandatetimeinput.h \
    qpersiandatetimewidget.h

FORMS    += mainwindow.ui \
    qpersiandatetimeinput.ui \
    qpersiandatetimewidget.ui

RESOURCES += \
    files.qrc
