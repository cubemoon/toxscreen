#include <cstdint>
#include <iostream>
#include <tox/tox.h>

#include "packet_handler.h"
#include "core.h"

PacketHandler * PacketHandler::pInstance{nullptr};

// Lazy proxy functions
int proxy_connect(void *object, const uint8_t *data, uint32_t len);
int proxy_info(void *object, const uint8_t *data, uint32_t len);

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
        tox_lossless_packet_registerhandler(tox, friendId, TOXSCREEN_ID_INFO, proxy_info, (void*)friendId);
        // Register Connect
        tox_lossless_packet_registerhandler(tox, friendId, TOXSCREEN_ID_CONNECT, proxy_connect, (void*)friendId);
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

int PacketHandler::handleConnect(void *object, const uint8_t *data, uint32_t len)
{
    // Todo
    return 0;
}

int PacketHandler::handleInfo(void *object, const uint8_t *data, uint32_t len)
{
    // Todo
    return 0;
}

int proxy_connect(void *object, const uint8_t *data, uint32_t len)
{
    return PacketHandler::getInstance()->handleConnect(object, data, len);
}

int proxy_info(void *object, const uint8_t *data, uint32_t len)
{
    return PacketHandler::getInstance()->handleInfo(object, data, len);
}
