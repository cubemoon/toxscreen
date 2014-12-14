#include <cstdint>

#include "friend.h"
#include "policy.h"

/**
 * Todo list:
 * - Friend::getPolicy() - Policy class describing
 *   what this friend is allowed to do. This might
 *   include default permission bitfield, whether
 *   connection requests should be ignored, etc.
 */

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
