#-------------------------------------------------
#
# Project created by QtCreator 2013-03-11T19:47:56
#
#-------------------------------------------------

QT       += core gui
QT       += webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ulis
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qtraceviewer.cpp \
    qreadgpx.cpp

HEADERS  += mainwindow.h \
    qtraceviewer.h \
    qreadgpx.h \
    TraceReaderInterface.h

FORMS    += mainwindow.ui
