#ifndef CORE_H
#define CORE_H

#include <cstdint>
#include <QByteArray>
#include <tox/tox.h>

// Function pointer for packet handler callbacks
typedef int (*packet_handler_callback)(void *object, const uint8_t *data, uint32_t len);

/**
 * Singleton core class that handles the tox instance.
 */
class Core
{
public:
    QByteArray getAddress();
    static Core * getInstance();
    Tox * getTox();
    bool hasTox();
    static Core * start();

private:
    Core();
    void initTox();

    Tox *pTox;
    static Core *pInstance;
};

#endif
