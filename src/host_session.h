#ifndef HOST_SESSION_H
#define HOST_SESSION_H

#include "friend.h"
#include "remote_action_manager.h"

class HostSession
{
public:
    HostSession();
    ~HostSession();
    void addGuest(Friend *_friend);
    void removeGuest(Friend *_friend);
    void removeGuest(int friendId);
private:
    std::vector<Friend*> *mGuests;
    RemoteActionManager *mRemote;
};

#endif
