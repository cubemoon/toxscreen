QT       += core gui testlib
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET   = toxscreen-tests
TEMPLATE = app
CONFIG   += c++11
QMAKE_CXXFLAGS += -Wno-unused-parameter

LIBS += -ltoxcore

unix {
    LIBS += -lX11
}

SOURCES += \
    ../src/packet/packet.cpp \
    src/main.cpp \
    src/test_packet.cpp

HEADERS += \
    ../src/packet/packet.h \
    src/test_packet.h
