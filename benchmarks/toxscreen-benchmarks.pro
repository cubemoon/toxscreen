QT       += core gui testlib
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET   = toxscreen-benchmarks
TEMPLATE = app
CONFIG   += c++11
QMAKE_CXXFLAGS += -Wno-unused-parameter

LIBS += -ltoxcore

unix {
    LIBS += -lX11
}

SOURCES += \
    ../src/screen_grabber.cpp \
    src/main.cpp \
    src/benchmark_screen_grabber.cpp

HEADERS += \
    ../src/screen_grabber.h \
    src/benchmark_screen_grabber.h
