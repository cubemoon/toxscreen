#ifdef __linux__

#include "remote_action_manager_x.h"

XRemoteActionManager::XRemoteActionManager()
    : RemoteActionManager()
{
    // Assuming this uses getenv("DISPLAY")
    pDisplay = XOpenDisplay(nullptr);
}

bool XRemoteActionManager::hasDisplay()
{
    return pDisplay != nullptr;
}

void XRemoteActionManager::click(int x, int y, int button)
{
    // Todo
}

void XRemoteActionManager::moveMouse(int x, int y)
{
    // For more information on this, see xdo_mouse_move implementation
    // in xdo.c (xdotool)
    if(hasDisplay())
    {
        Window screen = RootWindow(pDisplay, 0);
        int ret = XWarpPointer(pDisplay, None, screen, 0, 0, 0, 0, x, y);
        XFlush(pDisplay);

        if(ret != 0)
        {
            // Log error
        }
    }

    //if(hasXdo())
    //{
    //    xdo_mousemove(pXdo, x, y, 0);
    //}
}

#endif // __linux__
