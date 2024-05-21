#ifndef OnGround_State_h
#define OnGround_State_h

#include <Arduino.h>
#include "State.h"
#include "StateMachine.h"
#include "BuckeyContext.h"
#include "Timer.h"

#define PIR_PIN D5

class BuckeyContext;

enum OnGrourdEnum
{
    SEARCHING,
    IN_DELAY
};

class OnGroundState : public State
{

private:
    Timer *attentionTimer;

    int ATTENTION_CALL_INTERVAL = 30;

    // The amonnt of time between IR voice prompts
    int SEARCH_CALL_INTERVAL = 14;

    OnGrourdEnum inCallAction = OnGrourdEnum::SEARCHING;

    String pickMeUpSounds[4] = {"ImJustABucketAllBuyMyself", "HelloWillSomebodyPickMeUp", "HeyPickMeUp", "Whistle"};
    String dontputdown[2] = {"OhAreYouLeaving", "HeyDontLeaveMe"};
    String goodbyeSounds[1] = {"ThankYouForPlayingWithMe"};

    int count = 0;
    unsigned long languageCount = 0;

public:
    OnGroundState();
    void enter(BuckeyContext &data) override;
    void exit(BuckeyContext &data) override;
    void update(BuckeyContext &data) override;
};
#endif
