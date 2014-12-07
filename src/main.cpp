#include <iostream>
#include <QApplication>
#include <QByteArray>

#include "core.h"
#include "packet_handler.h"
#include "forms/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Core::start();
    PacketHandler::start();

    Core *core = Core::getInstance();

    // Print tox address
    std::cout << "address: " << core->getAddress().toHex().data() << std::endl;

    return a.exec();
}
