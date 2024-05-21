#include "WalkAroundState.h"

WalkAroundState::WalkAroundState()
{
    delayTimer = new Timer();
}

void WalkAroundState::enter(BuckeyContext &context)
{
    Serial.println("Walk Around State");

    String soundFileId = walkaround[random(2)];
    playSound(soundFileId);
    int time = 3 + (1.5 * BuckeyContext::sessionProgressCount);
    delayTimer->setTimer(time);
}

void WalkAroundState::exit(BuckeyContext &context)
{
}

void WalkAroundState::update(BuckeyContext &context)
{
    if (delayTimer->isExpired())
    {
        context.machine->setCurrentState(Singleton<InSessionState>::getInstance());
    }
}
