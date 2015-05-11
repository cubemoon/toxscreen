#include <iostream>
#include <QApplication>
#include <QByteArray>
#include <QGuiApplication>
#include <QPixmap>
#include <QtGlobal>

#include "core.h"
#include "packet_handler.h"
#include "screen_grabber.h"
#include "forms/main_window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    Core::start();
    //PacketHandler::start();

    Core *core = Core::getInstance();

    w.setTox(core->getTox());

    // Print tox address
    std::cout << "address: " << core->getTox()->getAddressHex().toStdString() << std::endl;
    std::cout << "public key: " << core->getTox()->getPublicKeyHex().toStdString() << std::endl;
    std::cout << "secret key: " << core->getTox()->getSecretKeyHex().toStdString() << std::endl;

    qDebug("Writing screenshot");
    ScreenGrabber grabber(QGuiApplication::primaryScreen());
    QPixmap ss = grabber.grabPixmap();
    ss.save(QString("screenshot.png"), "PNG");

    int result = app.exec();

    delete core;
    return result;
}
