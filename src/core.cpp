#include <cstdint>
#include <QByteArray>
#include "tox/toxcore.h"

#include "core.h"
#include "packet_handler.h"

Core * Core::pInstance{nullptr};

Core::Core()
    : mTox(ToxCore())
{
}

/**
 * Get a pointer to the singleton Core instance.
 * @return Pointer to singleton Core instance
 */
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
 * Get the Tox pointer.
 * @return pointer to Tox instance
 */
Tox * Core::getTox() const
{
    return mTox.getHandle();
}

/**
 * Whether or not we have a tox instance.
 * @return true if tox instance, false if nullptr
 */
bool Core::hasTox() const
{
    return mTox.hasHandle();
}

/**
 * Get our tox address. Will do nothing if no tox instance.
 * @return QByteArray containing address, or QByteArray filled with 0s
 *         if no tox
 */
QByteArray Core::getAddress() const
{
    std::vector<uint8_t> address = mTox.getAddress();
    return QByteArray((char *)address.data(), address.size());
}
