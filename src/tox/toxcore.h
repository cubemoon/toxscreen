#ifndef TOXSCREEN_TOX_TOXCORE_H
#define TOXSCREEN_TOX_TOXCORE_H

#include <cstdint>
#include <string>
#include <utility>
#include <vector>
#include <tox/tox.h>

typedef int (*tox_packet_handler_callback)(Tox *tox, int32_t friendnumber, const uint8_t *data, uint32_t len, void *object);

/**
 * Wrapper class for Tox instance defined in <tox/tox.h>.
 */
class ToxCore
{
public:
    ToxCore();
    ~ToxCore();
    std::vector<uint8_t> getAddress() const;
    Tox * getHandle() const;
    std::pair<std::vector<uint8_t>, std::vector<uint8_t>> getKeys(bool includePrivate = false) const;
    std::string getSelfStatusMessage();
    bool hasHandle() const;
    void registerHandlerLossless(int friendNum, uint8_t byte, tox_packet_handler_callback callback, void *object) const;
    void registerHandlerLossy(int friendNum, uint8_t byte, tox_packet_handler_callback callback, void *object) const;
    void sendLossless(int friendNum, const std::vector<uint8_t> data) const;
    void sendLosslessRaw(int friendNum, const uint8_t *data, uint32_t length) const;
    void sendLossy(int friendNum, const std::vector<uint8_t> data) const;
    void sendLossyRaw(int friendNum, const uint8_t *data, uint32_t length) const;
    void setStatusMessage(const std::string &message);
private:
    void initHandle();
    Tox *pTox;
};

#endif // TOXSCREEN_TOXCORE_H
