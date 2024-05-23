#include "InSessionState.h"
#include <Arduino.h>
#include "BuckeyContext.h"
#include "Singleton.h"
#include "SoundPlayer.h"
#include "ShakeRequestState.h"
#include "SwingRequestState.h"
#include "JumpRequestState.h"
#include "DanceRequestState.h"
#include "HugRequestState.h"
#include "WalkAroundState.h"

class BuckeyContext;

InSessionState::InSessionState()
{
    delayTimer = new Timer();
}

void InSessionState::enter(BuckeyContext &context)
{
    Serial.println("Entering State In Session: ");
    // Serial.println(BuckeyContext::currentBucketState);

    // delayTimer->setTimer(7);

    int time = 5;

    if (BuckeyContext::currentBucketState == BucketState::ONGROUND)
    {
        BuckeyContext::currentBucketState = BucketState::INSESSION;

        BuckeyContext::sessionProgressCount = 0;

        // play intro tp mew sessond sound/
        String soundFileId = pickedup[rand() % 2];
        Serial.print("Playing sound: ");
        Serial.println(soundFileId);
        playSound(soundFileId);
    }
    else
    {
        BuckeyContext::sessionProgressCount += 1;
    }
    delayTimer->setTimer(time);
}

void InSessionState::update(BuckeyContext &context)
{

    if (BuckeyContext::sessionProgressCount > 1 && BuckeyContext::sessionProgressCount % 2 != 0)
    {
        context.machine->setCurrentState(Singleton<WalkAroundState>::getInstance());
    }
    else
    {
        if (delayTimer->isExpired())
        {
            switch (requestIndex)
            {
            case RequestTypes::SHAKEBUCKET:
                context.machine->setCurrentState(Singleton<ShakeRequestState>::getInstance());
                break;
            case RequestTypes::DANCEBUCKET:
                context.machine->setCurrentState(Singleton<DanceRequestState>::getInstance());
                break;
            case RequestTypes::SWINGBUCKET:
                context.machine->setCurrentState(Singleton<SwingRequestState>::getInstance());
                break;
            case RequestTypes::JUMPBUCKET:
                context.machine->setCurrentState(Singleton<JumpRequestState>::getInstance());
                break;
            case RequestTypes::HUGBUCKET:
                context.machine->setCurrentState(Singleton<HugRequestState>::getInstance());
                break;
            }

            Serial.print("REQUESTING ACTION: ");
            Serial.println(requestIndex);
            requestIndex += 1;

            if (requestIndex >= 5)
            {
                requestIndex = 0;
            }
        }
    }
}

void InSessionState::exit(BuckeyContext &context)
{
}
