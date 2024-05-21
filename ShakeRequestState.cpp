#include "ShakeRequestState.h"
#include "SoundPlayer.h"
#include "InSessionState.h"

ShakeRequestState::ShakeRequestState()
{
    motionGesture = new ShakeGesture();
    delayTimer = new Timer();
}

void ShakeRequestState::enter(BuckeyContext &context)
{
    Serial.println("Enter Shake Request State");

    playSound("QuickWillYouShakeMe");
    delayTimer->setTimer(3);

    currentAction = RequestStateAction::MAKE_REQUEST;
    requestAttempts = 0;
}

void ShakeRequestState::exit(BuckeyContext &context)
{
}

void ShakeRequestState::update(BuckeyContext &context)
{
    if (currentAction == RequestStateAction::MAKE_REQUEST && delayTimer->isExpired())
    {
        // time to for user to perform actions
        delayTimer->setTimer(CHECK_GESTURE_TIME);
        currentAction = RequestStateAction::CHECK_GESTURE;
    }
    else if (currentAction == RequestStateAction::CHECK_GESTURE)
    {
        bool gestureSucess = motionGesture->calculateGesture(*context.motionController);

        if (gestureSucess)
        {
            // play sound

            playSound("OhYeahThatWasAGoodShake");
            Serial.println("Shake detected!!!!!!!!!!");
            currentAction = RequestStateAction::SUCESS;
        }
        else if (delayTimer->isExpired())
        {
            requestAttempts++;
            if (requestAttempts == 2)
            {
                // failed
                // Serial.println("Failed to detect shake gesture");
                context.machine->setCurrentState(Singleton<InSessionState>::getInstance());
            }
            else
            {
                // play request sound again  have them try again
                playSound("QuickWillYouShakeMe");

                delayTimer->setTimer(3);
                currentAction = RequestStateAction::MAKE_REQUEST;
            }
        }
    }
    else if (currentAction == RequestStateAction::SUCESS)
    {
        context.machine->setCurrentState(Singleton<InSessionState>::getInstance());
    }
}