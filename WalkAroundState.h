#ifndef _WalkArodund_State_h
#define _WalkArodund_State_h

#include <Arduino.h>
#include "State.h"
#include "BuckeyContext.h"
#include "InSessionState.h"

class BuckeyContext;

class WalkAroundState : public State
{

private:
    String walkaround[2] = {"YoureNiceWillYouShowMeAround", "OkLetsGoSeeSomething"};


public:
    WalkAroundState();
    void enter(BuckeyContext &data) override;
    void exit(BuckeyContext &data) override;
    void update(BuckeyContext &data) override;
};

#endif