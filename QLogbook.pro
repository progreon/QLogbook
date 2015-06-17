#-------------------------------------------------
#
# Project created by QtCreator 2015-06-16T14:42:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QLogbook
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logtablemodel.cpp \
    logentry.cpp

HEADERS  += mainwindow.h \
    logtablemodel.h \
    logentry.h

FORMS    += mainwindow.ui
