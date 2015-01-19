QT       += core gui testlib
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
    src/password_generator.cpp \
    src/policy.cpp \
    src/remote_action_manager.cpp \
    src/remote_action_manager_x.cpp \
    src/screen_grabber.cpp \
    src/packet/packet.cpp \
    src/qt/QTox.cpp \
    src/qt/QToxException.cpp \
    src/qt/QToxFileEncryptedException.cpp \
    src/qt/QToxReturnException.cpp \
    src/qt/QToxFriend.cpp \
    src/tox/exception.cpp \
    src/tox/toxcore.cpp \
    src/forms/connect_dialog.cpp \
    src/forms/main_window.cpp

HEADERS += \
    src/core.h \
    src/friend.h \
    src/host_session.h \
    src/password_generator.h \
    src/policy.h \
    src/remote_action_manager.h \
    src/remote_action_manager_x.h \
    src/screen_grabber.h \
    src/packet/packet.h \
    src/qt/QTox.h \
    src/qt/QToxException.h \
    src/qt/QToxFileEncryptedException.h \
    src/qt/QToxReturnException.h \
    src/qt/QToxFriend.h \
    src/tox/exception.h \
    src/tox/toxcore.h \
    src/forms/connect_dialog.h \
    src/forms/main_window.h

FORMS   += \
    src/forms/connect_dialog.ui \
    src/forms/main_window.ui
