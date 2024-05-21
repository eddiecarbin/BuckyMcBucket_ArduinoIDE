#ifndef _DanceReques_State_h
#define _DanceReques_State_h

#include <Arduino.h>
#include "State.h"
#include "BuckeyContext.h"
#include "DanceGesture.h"

class BuckeyContext;
// "dancerequest": [
//     "letsdance",
//     "dancewithme"
// ],
// "dancedetected": [
//     "greatrythm",
//     "agooddancer",
//     "thankfordance"
// ],
class DanceRequestState : public State
{
private:
    DanceGesture *motionGesture;
    boolean gestureSucess = false;
    

public:
    DanceRequestState();
    void enter(BuckeyContext &data) override;
    void exit(BuckeyContext &data) override;
    void update(BuckeyContext &data) override;
};

#endif