#ifndef REMOTE_ACTION_MANAGER_H
#define REMOTE_ACTION_MANAGER_H

/**
 * Handle remote actions. This will need to differ between platforms
 * considering differences in how events are triggered programatically.
 *
 * Might be beneficially to have a sort of Action queue that always
 * executes ordered?
 */
class RemoteActionManager
{
public:
    RemoteActionManager();
    virtual ~RemoteActionManager();
    virtual void click(int x, int y, int button);
    virtual void moveMouse(int x, int y);
};

#endif
