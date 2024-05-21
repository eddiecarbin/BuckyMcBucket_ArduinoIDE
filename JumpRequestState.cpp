#include "JumpRequestState.h"
#include "InSessionState.h"

JumpRequestState::JumpRequestState()
{
    delayTimer = new Timer();
    motionGesture = new JumpGesture();
}
void JumpRequestState::enter(BuckeyContext &context)
{
    Serial.println("Jump State");

    // String soundFileId = jumprequest[random(2)];
    playSound("OkLetsJumpAround");

    currentAction = RequestStateAction::MAKE_REQUEST;
    requestAttempts = 0;
    gestureSucess = false;
}

void JumpRequestState::exit(BuckeyContext &context)
{
}

void JumpRequestState::update(BuckeyContext &context)
{
    if (currentAction == RequestStateAction::MAKE_REQUEST)
    {
        if (!SoundPlayer.IsBusy())
        {
            // time to for user to perform actions
            delayTimer->setTimer(CHECK_GESTURE_TIME);

            playSound("JumpJumpJump");

            currentAction = RequestStateAction::CHECK_GESTURE;
        }
    }
    else if (currentAction == RequestStateAction::CHECK_GESTURE)
    {
        // gestureSucess = motionGesture->calculateGesture(*context.motionController);

        if (delayTimer->isExpired())
        {
            // if (gestureSucess)
            // {
            //     // play sound
            //     // String soundFileId = jumpdetected[0];
            // }
            playSound("IDoLoveToJumpYoureGood");
            delayTimer->setTimer(5);
            currentAction = RequestStateAction::SUCESS;
        }
    }
    else if (currentAction == RequestStateAction::SUCESS)
    {
        if (delayTimer->isExpired() && !SoundPlayer.IsBusy())
        {
            //  complete task reuts
            context.machine->setCurrentState(Singleton<InSessionState>::getInstance());
        }
    }
}