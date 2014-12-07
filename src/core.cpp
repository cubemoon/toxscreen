#include <cstdint>
#include <QByteArray>
#include <tox/tox.h>

#include "core.h"
#include "packet_handler.h"

Core * Core::pInstance{nullptr};

Core::Core()
    : pTox(nullptr)
{
    initTox();
}

Core * Core::getInstance()
{
    return Core::pInstance;
}

/**
 * Start the core. This will initialize the singleton instance.
 * @return singleton instance
 */
Core * Core::start()
{
    if(Core::getInstance() == nullptr)
    {
        Core *core = new Core();
        Core::pInstance = core;
        return core;
    }
    else
    {
        return Core::getInstance();
    }
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
