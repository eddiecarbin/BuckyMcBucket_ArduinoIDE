
#ifndef BuckeyContext_h
#define BuckeyContext_h

#include <Arduino.h>
#include <JC_Button.h>
#include "ToggleSwitchMonitor.h"
#include "MotionController.h"
#include "MotionGesture.h"
#include "SoundPlayer.h"
#include "Language.h"
#define LANGUAGE_BUTTON_PIN D6
#define VOLUME_BUTTON_PIN D8

class StateMachine;

enum class BucketState
{
    ONGROUND,
    INSESSION,
};

class BuckeyContext
{

private:
    ToggleSwitchMonitor *languageSwitchMonitor;
    Button *volumeButton;
    MotionGesture *motionGesture;
    BucketState previousState;

public:
    static BucketState currentBucketState;
    static Language currentLanguage;
    static int sessionProgressCount;

    MotionController *motionController;

    BuckeyContext();
    StateMachine *machine;

    void initialize();
    void update();

};

#endif