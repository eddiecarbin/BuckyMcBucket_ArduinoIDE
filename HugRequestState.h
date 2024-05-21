#ifndef _HugRequest_State_h
#define _HugRequest_State_h

#include <Arduino.h>
#include "State.h"
#include "BuckeyContext.h"

class BuckeyContext;

// "hugrequest": [
//     "ineedahug",
//     "givemeahug"
// ],
// "hugdetected": [
//     "thatsonice",
//     "thatfeelgood"
// ],
class HugRequestState : public State
{
private:

public:
    HugRequestState();
    void initialize();
    void enter(BuckeyContext &data) override;
    void exit(BuckeyContext &data) override;
    void update(BuckeyContext &data) override;
};

#endif