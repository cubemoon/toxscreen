#ifndef FRIEND_H
#define FRIEND_H

#include <cstdint>

class Friend
{
    private:
        int32_t mFriendId;

    public:
        Friend(int32_t friendId);
        int32_t getId();
};

#endif
