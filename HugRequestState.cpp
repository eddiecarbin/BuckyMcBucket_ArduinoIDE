#include "HugRequestState.h"
#include "SoundPlayer.h"
#include "InSessionState.h"

HugRequestState::HugRequestState()
{
    delayTimer = new Timer();
}

void HugRequestState::initialize()
{
}

void HugRequestState::enter(BuckeyContext &context)
{

    playSound("HiWillYouGiveMeAHug");

    currentAction = RequestStateAction::MAKE_REQUEST;
    delayTimer->setTimer(6);

    requestAttempts = 0;
}

void HugRequestState::exit(BuckeyContext &context)
{
}

void HugRequestState::update(BuckeyContext &context)
{

    if (currentAction == RequestStateAction::MAKE_REQUEST && delayTimer->isExpired())
    {
        if (!SoundPlayer.IsBusy())
        {
            // time to do actions
            delayTimer->setTimer(6);
            currentAction = RequestStateAction::CHECK_GESTURE;
        }
    }
    else if (currentAction == RequestStateAction::CHECK_GESTURE)
    {

        if (delayTimer->isExpired())
        {
            currentAction = RequestStateAction::SUCESS;
            // requestAttempts++;
            // if (requestAttempts == 2)
            // {
            //     context.machine->setCurrentState(Singleton<InSessionState>::getInstance());
            // }
            // else
            // {
            //     // play sound
            //     String soundFileId = hugrequest[0];
            //     playSound(soundFileId);
            //     currentAction = RequestStateAction::MAKE_REQUEST;
            // }
        }
    }
    else if (currentAction == RequestStateAction::SUCESS)
    {
        context.machine->setCurrentState(Singleton<InSessionState>::getInstance());
    }
}