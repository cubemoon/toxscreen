#include <cstdint>
#include <QByteArray>
#include "tox/toxcore.h"

#include "core.h"
#include "packet_handler.h"

Core * Core::pInstance{nullptr};

Core::Core()
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

QTox * Core::getTox()
{
    return &mTox;
}
