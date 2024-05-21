#ifndef _JumpRequest_State_h
#define _JumpRequest_State_h

#include <Arduino.h>
#include "State.h"
#include "BuckeyContext.h"
#include "JumpGesture.h"

class BuckeyContext;
class JumpRequestState : public State
{
private:
    // String jumprequest[2] = {"OkLetsJumpAround", "letsjump"};
    // String jumpdetected[1] = {"IDoLoveToJumpYoureGood"};
    bool gestureSucess = false;
    
    JumpGesture *motionGesture;

public:
    JumpRequestState();
    void enter(BuckeyContext &data) override;
    void exit(BuckeyContext &data) override;
    void update(BuckeyContext &data) override;
};

#endif