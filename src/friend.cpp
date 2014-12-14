#include <cstdint>

#include "friend.h"
#include "policy.h"

Friend::Friend(int32_t friendId)
    : mFriendId(friendId)
{
    pPolicy = new Policy();
}

Friend::~Friend()
{
    delete pPolicy;
}

/**
 * Get this friend's friend Id.
 * @return friend Id
 */
int32_t Friend::getId()
{
    return this->mFriendId;
}

/**
 * Get this friend's policy.
 * @return policy
 */
Policy * Friend::getPolicy()
{
    return pPolicy;
}
