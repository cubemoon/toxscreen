#include "friend.h"
#include "policy.h"

Policy::Policy()
{
    mCanClick = false;
    mCanType = false;
}

bool Policy::canClick()
{
    return mCanClick;
}

bool Policy::canType()
{
    return mCanType;
}
