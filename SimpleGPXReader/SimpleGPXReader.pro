#-------------------------------------------------
#
# Project created by QtCreator 2013-03-19T21:10:21
#
#-------------------------------------------------

QT       += xml core

QT       -= gui

TARGET = SimpleGPXReader

TEMPLATE = lib

DEFINES += SIMPLEGPXREADER_LIBRARY

SOURCES += simplegpxreader.cpp \
    TraceData.cpp

HEADERS += simplegpxreader.h\
        SimpleGPXReader_global.h \
        TraceData.h \
        Node.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

#win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/release/
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/debug/
#else:unix: LIBS += -L$$OUT_PWD/
LIBS += -L$$OUT_PWD/

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/

QMAKE_CXXFLAGS += -std=c++11
