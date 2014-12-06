#include <cstdint>

#include "core.h"
#include <tox/tox.h>

Core::Core()
{
    initTox();
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
