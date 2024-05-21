#include "SwingRequestState.h"
#include "InSessionState.h"

SwingRequestState::SwingRequestState()
{
    delayTimer = new Timer();
    motionGesture = new SwingGesture();
}

void SwingRequestState::enter(BuckeyContext &context)
{
    Serial.println("Enter Dance Request State");

    playSound("OkILikeToSwingSwingMe");

    currentAction = RequestStateAction::MAKE_REQUEST;
    requestAttempts = 0;
}

void SwingRequestState::exit(BuckeyContext &context)
{
}

void SwingRequestState::update(BuckeyContext &context)
{
    if (currentAction == RequestStateAction::MAKE_REQUEST)
    {
        if (!SoundPlayer.IsBusy())
        {
            // time to for user to perform actions
            delayTimer->setTimer(CHECK_GESTURE_TIME);
            currentAction = RequestStateAction::CHECK_GESTURE;
        }
    }
    else if (currentAction == RequestStateAction::CHECK_GESTURE)
    {
        bool gestureSucess = motionGesture->calculateGesture(*context.motionController);
        if (gestureSucess)
        {
            // play sound
            playSound("WeeThatsSoFun");
            currentAction = RequestStateAction::SUCESS;
        }
        else if (delayTimer->isExpired())
        {
            requestAttempts++;
            if (requestAttempts == 2)
            {
                // failed
                context.machine->setCurrentState(Singleton<InSessionState>::getInstance());
            }
            else
            {
                playSound("OkILikeToSwingSwingMe");

                currentAction = RequestStateAction::MAKE_REQUEST;
            }
        }
    }
    else if (currentAction == RequestStateAction::SUCESS)
    {
        if (!SoundPlayer.IsBusy())
        {
            //  complete task reuts
            context.machine->setCurrentState(Singleton<InSessionState>::getInstance());
        }
    }
}