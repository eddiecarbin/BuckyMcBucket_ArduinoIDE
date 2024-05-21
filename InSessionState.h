
#ifndef InSession_State_h
#define InSession_State_h

#include <Arduino.h>
#include "State.h"
#include "StateMachine.h"
#include "BuckeyContext.h"
#include "Timer.h"

#define END_SOUND_DELAY 8

class BuckeyContext;

enum RequestTypes
{
    SHAKEBUCKET,
    DANCEBUCKET,
    SWINGBUCKET,
    JUMPBUCKET,
    HUGBUCKET
};

class InSessionState : public State
{

private:
    int requestIndex = 0;

    int completedSessionRequest = 0;

    String pickedup[2] = {
        "OkLetsGoSeeSomething",
        "HiImBuckyLetsGo"};


public:
    InSessionState();
    void enter(BuckeyContext &data) override;
    void exit(BuckeyContext &data) override;
    void update(BuckeyContext &data) override;
};

#endif