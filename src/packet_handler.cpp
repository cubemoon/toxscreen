#include <cstdint>
#include <iostream>
#include <tox/tox.h>

#include "packet_handler.h"
#include "core.h"

PacketHandler * PacketHandler::pInstance{nullptr};

// Lazy proxy functions
int proxy_connect(Tox *tox, int32_t friendId, const uint8_t *data, uint32_t len, void *object);
int proxy_info(Tox *tox, int32_t friendId, const uint8_t *data, uint32_t len, void *object);

PacketHandler::PacketHandler()
{
}

/**
 * Register packet handlers for a friend.
 * @param friend Friend Id to add handlers for
 * @return true if successful, false if not
 */
bool PacketHandler::registerFor(int32_t friendId)
{
    Tox *tox = Core::getInstance()->getTox();

    if(tox != nullptr)
    {
        // Register Info
        tox_lossless_packet_registerhandler(tox, friendId, TOXSCREEN_ID_INFO, proxy_info, NULL);
        // Register Connect
        tox_lossless_packet_registerhandler(tox, friendId, TOXSCREEN_ID_CONNECT, proxy_connect, NULL);
        return true;
    }

    return false;
}

PacketHandler * PacketHandler::getInstance()
{
    return pInstance;
}

PacketHandler * PacketHandler::start()
{
    if(PacketHandler::getInstance() == nullptr)
    {
        PacketHandler::pInstance = new PacketHandler();
    }

    return PacketHandler::getInstance();
}

int PacketHandler::handleConnect(Tox *tox, int32_t friendId, const uint8_t *data, uint32_t len, void *object)
{
    // Todo
    return 0;
}

int PacketHandler::handleInfo(Tox *tox, int32_t friendId, const uint8_t *data, uint32_t len, void *object)
{
    // Todo
    return 0;
}

int proxy_connect(Tox *tox, int32_t friendId, const uint8_t *data, uint32_t len, void *object)
{
    return PacketHandler::getInstance()->handleConnect(tox, friendId, data, len, object);
}

int proxy_info(Tox *tox, int32_t friendId, const uint8_t *data, uint32_t len, void *object)
{
    return PacketHandler::getInstance()->handleInfo(tox, friendId, data, len, object);
}
