#-------------------------------------------------
#
# Project created by QtCreator 2015-06-16T14:42:18
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QLogbook
TEMPLATE = app


SOURCES += main.cpp\
    model/logbookmodel.cpp \
    model/logentry.cpp \
    model/logtablemodel.cpp \
    view/entrydialog.cpp \
    view/mainwindow.cpp \
    model/entrytype.cpp \
    view/descriptiondialog.cpp

HEADERS  += \
    model/logbookmodel.h \
    model/logentry.h \
    model/logtablemodel.h \
    view/entrydialog.h \
    view/mainwindow.h \
    model/entrytype.h \
    view/descriptiondialog.h

FORMS    += \
    view/entrydialog.ui \
    view/mainwindow.ui \
    view/descriptiondialog.ui
