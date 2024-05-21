#ifndef _SwingRequest_State_h
#define _SwingRequest_State_h

#include <Arduino.h>
#include "State.h"
#include "BuckeyContext.h"
#include "SwingGesture.h"

class BuckeyContext;

class SwingRequestState : public State
{
private:
    SwingGesture *motionGesture;

public:
    SwingRequestState();
    void enter(BuckeyContext &data) override;
    void exit(BuckeyContext &data) override;
    void update(BuckeyContext &data) override;
};

#endif