#include <cstdint>
#include <QByteArray>
#include <tox/tox.h>

#include "core.h"

Core::Core()
    : pTox(nullptr)
{
}

/**
 * Start this core instance.
 */
void Core::start()
{
    initTox();
}

/**
 * Initialize the tox instance.
 */
void Core::initTox()
{
    pTox = tox_new(nullptr);
    // Todo: Load from file
}

/**
 * Get the Tox pointer.
 * @return pointer to Tox instance
 */
Tox *Core::getTox()
{
    return pTox;
}

/**
 * Whether or not we have a tox instance.
 * @return true if tox instance, false if nullptr
 */
bool Core::hasTox()
{
    return pTox != nullptr;
}

/**
 * Get our tox address. Will do nothing if no tox instance.
 * @return QByteArray containing address, or QByteArray filled with 0s
 *         if no tox
 */
QByteArray Core::getAddress()
{
    if(hasTox())
    {
        uint8_t buffer[TOX_FRIEND_ADDRESS_SIZE];
        tox_get_address(pTox, buffer);
        return QByteArray((const char *)buffer, TOX_FRIEND_ADDRESS_SIZE);
    }
    else
    {
        return QByteArray(TOX_FRIEND_ADDRESS_SIZE, 0);
    }
}
