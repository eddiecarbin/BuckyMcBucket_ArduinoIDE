#include <Arduino.h>
#include "BuckeyContext.h"
#include "OnGroundState.h"
#include "InSessionState.h"
#include "ToggleSwitchMonitor.h"
#include "MotionController.h"
#include "SoundPlayer.h"
#include "MotionGesture.h"

int BuckeyContext::sessionProgressCount = 0;

BuckeyContext::BuckeyContext()
{
}

BucketState BuckeyContext::currentBucketState = BucketState::ONGROUND;
Language BuckeyContext::currentLanguage = Language::ENGLISH;

void BuckeyContext::initialize()
{
    motionController = new MotionController();

    machine = new StateMachine(*this, Singleton<OnGroundState>::getInstance());

    languageSwitchMonitor = new ToggleSwitchMonitor(LANGUAGE_BUTTON_PIN);

    motionGesture = new MotionGesture();

    languageSwitchMonitor->update();
    BuckeyContext::currentLanguage = (languageSwitchMonitor->getState() == 1) ? Language::ENGLISH : Language::SPANISH;

    volumeButton = new Button(VOLUME_BUTTON_PIN);
    pinMode(VOLUME_BUTTON_PIN, INPUT_PULLUP);

    volumeButton->begin();
}

void BuckeyContext::update()
{
    motionController->update();

    if (languageSwitchMonitor->update() == true)
    {
        BuckeyContext::currentLanguage = (languageSwitchMonitor->getState() == 1) ? Language::ENGLISH : Language::SPANISH;

        float duration = SoundPlayer.playSoundByName("OkLetsSpeak", BuckeyContext::currentLanguage);
        delay(duration * 1200);

        previousState = BuckeyContext::currentBucketState;
        // BuckeyContext::currentBucketState = BucketState::SETTINGS;
    }

    // if (BuckeyContext::currentBucketState == BucketState::SETTINGS)
    // {
    // if (SoundPlayer.IsBusy())
    // {
    //     return;
    // }
    // BuckeyContext::currentBucketState = previousState;
    // }

    volumeButton->read();

    if (volumeButton->wasReleased())
    {
        Serial.println("volume button released");
        SoundPlayer.changeVolume();
        float duration = SoundPlayer.playSoundByName("ImBucky", Language::ENGLISH);
        delay(duration * 1200);
    }

    machine->update();

    bool detectMotion = motionGesture->calculateGesture(*motionController);

    if (BuckeyContext::currentBucketState == BucketState::ONGROUND && detectMotion)
    {
        machine->setCurrentState(Singleton<InSessionState>::getInstance());

        Serial.println("IN SESSION");
    }
    else if (BuckeyContext::currentBucketState != BucketState::ONGROUND && !detectMotion)
    {
        machine->setCurrentState(Singleton<OnGroundState>::getInstance());
        Serial.println("ON GROUND");
    }
}