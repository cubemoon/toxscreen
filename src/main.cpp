#include <iostream>
#include <QApplication>
#include <QByteArray>

#include "core.h"
#include "forms/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // Print tox address
    Core *core = new Core();
    core->start();
    std::cout << "address: " << core->getAddress().toHex().data() << std::endl;

    return a.exec();
}
