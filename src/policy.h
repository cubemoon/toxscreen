#ifndef POLICY_H
#define POLICY_H

class Policy {
public:
    Policy();
    bool canClick();
    bool canType();
private:
    bool mCanClick;
    bool mCanType;
};

#endif
