#ifndef REMOTE_ACTION_MANAGER_X_H
#define REMOTE_ACTION_MANAGER_X_H

#include <X11/Xlib.h>
#include "remote_action_manager.h"

class XRemoteActionManager: public RemoteActionManager
{
public:
    XRemoteActionManager();
    void click(int x, int y, int button);
    bool hasDisplay();
    void moveMouse(int x, int y);
private:
    Display *pDisplay;
};

#endif
