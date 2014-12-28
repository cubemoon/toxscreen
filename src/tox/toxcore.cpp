#include <algorithm>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>
#include "exception.h"
#include "toxcore.h"

/**
 * Construct a default ToxCore instance. Will pass `nullptr` to
 * tox_new(3), indicating default settings.
 */
ToxCore::ToxCore()
    : pTox(nullptr)
{
    initHandle();
}

/**
 * Destruct this ToxCore instance. Will call tox_kill(3) on the
 * handle.
 */
ToxCore::~ToxCore()
{
    if(hasHandle())
    {
        tox_kill(getHandle());
    }
}

/**
 * Get the Tox handle instance.
 * @return Tox handle
 */
Tox * ToxCore::getHandle() const
{
    return pTox;
}

/**
 * Get the Tox address.
 * @return address
 */
std::vector<uint8_t> ToxCore::getAddress() const
{
    if(hasHandle())
    {
        std::vector<uint8_t> bytes(TOX_FRIEND_ADDRESS_SIZE);
        tox_get_address(getHandle(), (uint8_t*)bytes.data());
        return bytes;
    }
    else
    {
        throw ToxNullHandleException();
    }
}

/**
 * Get the Tox keys.
 * @param includePrivate Whether or not to get the private key as well.
 * @return std::pair of public and private keys as std::vectors of
 *         uint8_t. The private key will be empty if {@param includePrivate}
 *         was false.
 */
std::pair<std::vector<uint8_t>, std::vector<uint8_t>>
ToxCore::getKeys(bool includePrivate) const
{
    if(hasHandle())
    {
        int privsize = (includePrivate ? TOX_CLIENT_ID_SIZE : 0);
        std::vector<uint8_t> pubkey(TOX_CLIENT_ID_SIZE);
        std::vector<uint8_t> privkey(privsize);

        if(includePrivate)
            tox_get_keys(getHandle(), pubkey.data(), privkey.data());
        else
            tox_get_keys(getHandle(), pubkey.data(), nullptr);

        std::pair<std::vector<uint8_t>, std::vector<uint8_t>> keys(pubkey, privkey);
        return keys;
    }
    else
    {
        throw ToxNullHandleException();
    }
}

/**
 * Get the status message of this user.
 * @return Status message
 */
std::string ToxCore::getSelfStatusMessage()
{
    if(hasHandle())
    {
        int size = tox_get_self_status_message_size(getHandle());
        if(size >= 0)
        {
            uint8_t buffer[size];
            int result;
            if((result = tox_get_self_status_message(getHandle(), buffer, size)) == size)
            {
                return std::string((char*)buffer, (size_t)size);
            }

            throw ToxReturnException("tox_get_self_status_message", size, result);
        }

        throw ToxNegativeReturnException("tox_get_self_status_message_size", size);
    }

    throw ToxNullHandleException();
}

/**
 * Check whether or not the Tox handle is valid (not null).
 * @return true if valid, false if not
 */
bool ToxCore::hasHandle() const
{
    return pTox != nullptr;
}

/**
 * Initialize the Tox handle.
 */
void ToxCore::initHandle()
{
    pTox = tox_new(nullptr);
}

/**
 * Set the status message for this user.
 * @param message Status message to set
 */
void ToxCore::setStatusMessage(const std::string &message)
{
    if(hasHandle())
    {
        uint16_t size = std::min<int>(message.size(), TOX_MAX_STATUSMESSAGE_LENGTH);
        int result = tox_set_status_message(getHandle(), (uint8_t*)message.c_str(), size);

        if(result != 0)
        {
            throw ToxNonZeroReturnException("tox_set_status_message", result);
        }
    }
    else
    {
        throw ToxNullHandleException();
    }
}

/**
 * Register a handler for lossy packets.
 * @param friendNum Friend to register the handler for
 * @param byte Byte identifier
 * @param callback Callback function pointer
 * @param object Pointer to extra data that will be passed to {@param callback}
 * @throw ToxNonZeroReturnException
 * @throw ToxNullHandleException
 */
void ToxCore::registerHandlerLossy(int friendNum, uint8_t byte, tox_packet_handler_callback callback, void *object) const
{
    if(hasHandle())
    {
        int success = tox_lossy_packet_registerhandler(getHandle(), friendNum, byte, callback, object);

        if(success != 0)
        {
            throw ToxNonZeroReturnException("tox_lossy_packet_registerhandler", success);
        }
    }
    else
    {
        throw ToxNullHandleException();
    }
}

/**
 * Send a lossy packet. Wrapper method for sendLossyRaw.
 * @param friendNum Friend to send packet to
 * @param data Data to send
 * @see ToxCore::sendLossyRaw(int, const uint8_t*, uint32_t)
 * @throw ToxNonZeroReturnException
 * @throw ToxNullHandleException
 */
void ToxCore::sendLossy(int friendNum, const std::vector<uint8_t> data) const
{
    sendLossyRaw(friendNum, data.data(), data.size());
}

/**
 * Send a lossy packet.
 * @param friendNum Friend to send packet to
 * @param data Data to send
 * @param length Amount of data
 * @throw ToxNonZeroReturnException
 * @throw ToxNullHandleException
 */
void ToxCore::sendLossyRaw(int friendNum, const uint8_t *data, uint32_t length) const
{
    if(hasHandle())
    {
        int success = tox_send_lossy_packet(getHandle(), friendNum, data, length);

        if(success != 0)
        {
            throw ToxNonZeroReturnException("tox_send_lossy_packet", success);
        }
    }
    else
    {
        throw ToxNullHandleException();
    }
}

/**
 * Register a handler for lossless packets.
 * @param friendNum Friend to register the handler for
 * @param byte Byte identifier
 * @param callback Callback function pointer
 * @param object Pointer to extra data that will be passed to {@param callback}
 * @throw ToxNonZeroReturnException
 * @throw ToxNullHandleException
 */
void ToxCore::registerHandlerLossless(int friendNum, uint8_t byte, tox_packet_handler_callback callback, void *object) const
{
    if(hasHandle())
    {
        int success = tox_lossless_packet_registerhandler(getHandle(), friendNum, byte, callback, object);

        if(success != 0)
        {
            throw ToxNonZeroReturnException("tox_lossless_packet_registerhandler", success);
        }
    }
    else
    {
        throw ToxNullHandleException();
    }
}

/**
 * Send a lossless packet. Wrapper method for sendLosslessRaw.
 * @param friendNum Friend to send packet to
 * @param data Data to send
 * @see ToxCore::sendLosslessRaw(int, const uint8_t*, uint32_t)
 * @throw ToxNonZeroReturnException
 * @throw ToxNullHandleException
 */
void ToxCore::sendLossless(int friendNum, const std::vector<uint8_t> data) const
{
    sendLosslessRaw(friendNum, data.data(), data.size());
}

/**
 * Send a lossless packet.
 * @param friendNum Friend to send packet to
 * @param data Data to send
 * @param length Amount of data
 * @throw ToxNonZeroReturnException
 * @throw ToxNullHandleException
 */
void ToxCore::sendLosslessRaw(int friendNum, const uint8_t *data, uint32_t length) const
{
    if(hasHandle())
    {
        int success = tox_send_lossless_packet(getHandle(), friendNum, data, length);

        if(success != 0)
        {
            throw ToxNonZeroReturnException("tox_send_lossless_packet", success);
        }
    }
    else
    {
        throw ToxNullHandleException();
    }
}
