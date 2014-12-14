QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = toxscreen
TEMPLATE = app
CONFIG   += c++11

LIBS += -ltoxcore

SOURCES += \
    src/main.cpp \
    src/core.cpp \
    src/friend.cpp \
    src/packet_handler.cpp \
    src/policy.cpp \
    src/forms/mainwindow.cpp

HEADERS += \
    src/core.h \
    src/friend.h \
    src/packet_handler.h \
    src/policy.h \
    src/forms/mainwindow.h

FORMS   += \
    src/forms/mainwindow.ui
