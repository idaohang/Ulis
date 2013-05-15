#-------------------------------------------------
#
# Project created by QtCreator 2013-03-21T08:31:32
#
#-------------------------------------------------

QT       += xml testlib

QT       -= gui

TARGET = simplegpxreader_test
CONFIG   += console
CONFIG   -= app_bundle

HEADERS += ../../Ulis/SimpleGPXReader/Node.h

TEMPLATE = app

LIBS += -L../SimpleGPXReader/debug -lSimpleGPXReader
INCLUDEPATH += ../../Ulis/SimpleGPXReader/

SOURCES += simplegpxreader_test.cpp
DEFINES += SRCDIR=\"$$PWD\"

OTHER_FILES += \
    txt_GPX_NoTrack.gpx \
    txt_GPX_OneTrk.gpx

for(FILE, OTHER_FILES) {
    FILE_CPY = $$quote($$PWD/$$FILE) $$quote($$OUT_PWD)
    QMAKE_POST_LINK += $$QMAKE_COPY $$replace( FILE_CPY, /, \\) $$escape_expand(\\n\\t)
}

QMAKE_CXXFLAGS += -std=c++11
