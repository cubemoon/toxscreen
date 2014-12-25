#include <iostream>
#include <QApplication>
#include <QByteArray>
#include <QGuiApplication>
#include <QPixmap>

#include "core.h"
#include "packet_handler.h"
#include "screen_grabber.h"
#include "forms/mainwindow.h"

int main(int argc, char *argv[])
{
    // The order of these two matters, guiApp needed for QScreen
    QGuiApplication guiApp(argc, argv);
    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    Core::start();
    PacketHandler::start();

    Core *core = Core::getInstance();

    // Print tox address
    std::cout << "address: " << core->getAddress().toHex().data() << std::endl;

    ScreenGrabber grabber(guiApp.primaryScreen());
    QPixmap ss = grabber.grabPixmap();
    ss.save(QString("screenshot.png"), "PNG");

    return app.exec();
}
