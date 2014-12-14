#include <vector>
#include "friend.h"
#include "host_session.h"

#include "remote_action_manager.h"
#ifdef __linux__
#include "remote_action_manager_x.h"
#endif

HostSession::HostSession()
{
  mGuests = new std::vector<Friend*>();

  // Setup remote action manager (platform dependant)
#ifdef __linux__
    mRemote = new XRemoteActionManager();
#else
    mRemote = nullptr;
#endif
}

HostSession::~HostSession()
{
    delete mGuests;

    if(mRemote != nullptr)
    {
        delete mRemote;
    }
}

void HostSession::addGuest(Friend *_friend)
{
    // Todo
}

void HostSession::removeGuest(Friend *_friend)
{
    // Todo
}

void HostSession::removeGuest(int friendId)
{
    // Todo
}
