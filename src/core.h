#ifndef CORE_H
#define CORE_H

#include <cstdint>
#include <QByteArray>
#include <tox/tox.h>

// Function pointer for packet handler callbacks
typedef int (*packet_handler_callback)(void *object, const uint8_t *data, uint32_t len);

typedef struct _ToxAddress {
    uint8_t value[TOX_FRIEND_ADDRESS_SIZE];
} ToxAddress;

/**
 * Singleton core class that handles the tox instance.
 */
class Core
{
    private:
        Tox *pTox;
        void initTox();

    public:
        Core();
        Tox *getTox();
        QByteArray getAddress();
        bool hasTox();
        void start();
};

#endif
