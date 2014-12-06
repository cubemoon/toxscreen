#include <cstdint>

#include "friend.h"

/**
 * Todo list:
 * - Friend::getPolicy() - Policy class describing
 *   what this friend is allowed to do. This might
 *   include default permission bitfield, whether
 *   connection requests should be ignored, etc.
 */

Friend::Friend(int32_t friendId) :
    mFriendId(friendId)
{
}

/**
 * Get this friend's friend Id.
 * @return friend Id
 */
int32_t Friend::getId()
{
    return this->mFriendId;
}
