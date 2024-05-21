#include "DanceRequestState.h"
#include "InSessionState.h"

DanceRequestState::DanceRequestState()
{
    motionGesture = new DanceGesture();
    delayTimer = new Timer();
}

void DanceRequestState::enter(BuckeyContext &context)
{

    playSound("HeyletsDance");

    requestAttempts = 0;
    currentAction = RequestStateAction::MAKE_REQUEST;
    delayTimer->setTimer(3);

    gestureSucess = false;
}

void DanceRequestState::exit(BuckeyContext &context)
{
}

void DanceRequestState::update(BuckeyContext &context)
{
    if (currentAction == RequestStateAction::MAKE_REQUEST && delayTimer->isExpired())
    {
        playSound("BeatBox");
        // time to for user to perform actions
        delayTimer->setTimer(5);
        currentAction = RequestStateAction::CHECK_GESTURE;
    }
    else if (currentAction == RequestStateAction::CHECK_GESTURE)
    {
        // gestureSucess = motionGesture->calculateGesture(*context.motionController);

        if (delayTimer->isExpired())
        {
            int time = 1;
            // if (gestureSucess)
            // {
            // }
            time += playSound("YoureAGoodDancer");
            delayTimer->setTimer(time);
            currentAction = RequestStateAction::SUCESS;
        }
    }
    else if (currentAction == RequestStateAction::SUCESS)
    {
        if (delayTimer->isExpired())
        {
            //  complete task reuts
            context.machine->setCurrentState(Singleton<InSessionState>::getInstance());
        }
    }
}