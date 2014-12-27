#include <algorithm>
#include <cstdint>
#include <sstream>
#include <string>
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
