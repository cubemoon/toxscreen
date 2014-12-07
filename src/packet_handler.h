#ifndef PACKET_HANDLER_H
#define PACKET_HANDLER_H

#include <cstdint>

#define TOXSCREEN_ID_INFO 160
#define TOXSCREEN_ID_CONNECT 161

class PacketHandler
{
public:
    static PacketHandler * getInstance(); // Singleton instance
    int handleConnect(void *object, const uint8_t *data, uint32_t len);
    int handleInfo(void *object, const uint8_t *data, uint32_t len);
    bool registerFor(int32_t friendId);
    static PacketHandler * start();

private:
    PacketHandler();

    static PacketHandler *pInstance;
};

#endif
