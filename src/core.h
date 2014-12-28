#ifndef TOXSCREEN_CORE_H
#define TOXSCREEN_CORE_H

#include <cstdint>
#include <QByteArray>
#include "tox/toxcore.h"

// Function pointer for packet handler callbacks
typedef int (*packet_handler_callback)(void *object, const uint8_t *data, uint32_t len);

/**
 * Singleton core class that handles the tox instance.
 */
class Core
{
public:
    QByteArray getAddress() const;
    static Core * getInstance();
    QByteArray getPrivateKey() const;
    QByteArray getPublicKey() const;
    Tox * getTox() const;
    bool hasTox() const;
    static Core * start();
private:
    Core();
    ToxCore mTox;
    static Core *pInstance;
};

#endif
