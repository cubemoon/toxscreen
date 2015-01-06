#ifndef TOXSCREEN_CORE_H
#define TOXSCREEN_CORE_H

#include <cstdint>
#include <QByteArray>
#include "qt/QTox.h"

/**
 * Singleton core class that handles the tox instance.
 */
class Core
{
public:
    static Core * getInstance();
    static Core * start();
    QTox * getTox();
private:
    Core();
    QTox mTox;
    static Core *pInstance;
};

#endif
