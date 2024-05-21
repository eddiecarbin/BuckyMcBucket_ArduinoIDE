#ifndef _ShakeRequest_State_h
#define _ShakeRequest_State_h

#include <Arduino.h>
#include "State.h"
#include "BuckeyContext.h"
#include "ShakeGesture.h"
#include "Timer.h"

class BuckeyContext;
//  "shakebucket": {
//         "request": "shakerequest",
//         "detected": "shakedetected"
//     },

//   "shakerequest": [
//         "quickshakeme"
//     ],

//             "shakedetected": [
//         "ineededthat",
//         "thatwasgood",
//         "agoodshake"
//     ],


class ShakeRequestState : public State
{
private:
    ShakeGesture *motionGesture;


public:
    ShakeRequestState();
    void enter(BuckeyContext &data) override;
    void exit(BuckeyContext &data) override;
    void update(BuckeyContext &data) override;
};

#endif