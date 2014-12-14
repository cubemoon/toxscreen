#ifndef FRIEND_H
#define FRIEND_H

#include <cstdint>

#include "policy.h"

class Friend
{
public:
    Friend(int32_t friendId);
    ~Friend();
    int32_t getId();
    Policy * getPolicy();
private:
    int32_t mFriendId;
    Policy *pPolicy;
};

#endif
