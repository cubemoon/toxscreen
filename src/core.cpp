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
 * Get our address.
 * @return QByteArray with address
 */
QByteArray Core::getAddress() const
{
    std::vector<uint8_t> address = mTox.getAddress();
    return QByteArray((char *)address.data(), address.size());
}

/**
 * Get our public key.
 * @return QByteArray with public key
 */
QByteArray Core::getPublicKey() const
{
    std::vector<uint8_t> key = mTox.getKeys(false).first;
    return QByteArray((char *)key.data(), key.size());
}

/**
 * Get our private key.
 * @return QByteArray with private key
 */
QByteArray Core::getPrivateKey() const
{
    std::vector<uint8_t> key = mTox.getKeys(true).second;
    return QByteArray((char *)key.data(), key.size());
}
