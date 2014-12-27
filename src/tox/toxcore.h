#ifndef TOXSCREEN_TOX_TOXCORE_H
#define TOXSCREEN_TOX_TOXCORE_H

#include <cstdint>
#include <string>
#include <vector>
#include <tox/tox.h>

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
    std::string getSelfStatusMessage();
    bool hasHandle() const;
    void setStatusMessage(const std::string &message);
private:
    void initHandle();
    Tox *pTox;
};

#endif // TOXSCREEN_TOXCORE_H
