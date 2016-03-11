#-------------------------------------------------
#
# Project created by QtCreator 2016-03-07T23:47:05
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CDBEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sqlitemanager.cpp

HEADERS  += mainwindow.h \
    sqlitemanager.h

FORMS    += mainwindow.ui

RESOURCES += \
    icons.qrc

DISTFILES +=
