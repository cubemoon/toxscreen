QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET   = toxscreen
TEMPLATE = app
CONFIG   += c++11
QMAKE_CXXFLAGS += -Wno-unused-parameter

LIBS += -ltoxcore

unix {
    LIBS += -lX11
}

SOURCES += \
    src/main.cpp \
    src/core.cpp \
    src/friend.cpp \
    src/host_session.cpp \
    src/packet_handler.cpp \
    src/policy.cpp \
    src/remote_action_manager.cpp \
    src/remote_action_manager_x.cpp \
    src/screen_grabber.cpp \
    src/forms/mainwindow.cpp

HEADERS += \
    src/core.h \
    src/friend.h \
    src/host_session.h \
    src/packet_handler.h \
    src/policy.h \
    src/remote_action_manager.h \
    src/remote_action_manager_x.h \
    src/screen_grabber.h \
    src/forms/mainwindow.h

FORMS   += \
    src/forms/mainwindow.ui
