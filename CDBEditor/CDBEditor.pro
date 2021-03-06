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
    sqlitemanager.cpp \
    dialognewseriesorig.cpp

HEADERS  += mainwindow.h \
    sqlitemanager.h \
    dialognewseriesorig.h

FORMS    += mainwindow.ui \
    dialognewseriesorig.ui

RESOURCES += \
    icons.qrc

DISTFILES +=

install_it.path = $$OUT_PWD
install_it.files = *.db

INSTALLS += \
    install_it
