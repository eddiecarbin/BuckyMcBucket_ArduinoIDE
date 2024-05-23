#ifndef STATE_H__
#define STATE_H__

#include <Arduino.h>
#include "Singleton.h"
// #include "StateMachine.h"
#include <stdio.h>
#include "BuckeyContext.h"
#include "SoundPlayer.h"
#include "Timer.h"

// https://github.com/Arekushi/Finite-State-Machine-Arduino

#define CHECK_GESTURE_TIME 5


enum class RequestStateAction
{
    MAKE_REQUEST,
    CHECK_GESTURE,
    SUCESS,
    FALIED
};

class State
{
    friend class Singleton<BuckeyContext>;

    // protected:
    //     using base = State;
protected:
    Timer *delayTimer;
    int requestAttempts = 0;
    RequestStateAction currentAction = RequestStateAction::MAKE_REQUEST;

public:
    bool hasSetup = false;

    const String name;

    State(const String name) : name(name)
    {
        hasSetup = false;
    }

    State()
    {
        hasSetup = false;
    }

    virtual ~State()
    {
    }

    void setup()
    {
        hasSetup = true;
    }

    virtual void enter(BuckeyContext &data) = 0;

    virtual void exit(BuckeyContext &data) = 0;

    virtual void update(BuckeyContext &data) = 0;

    // https://stackoverflow.com/questions/307765/how-do-i-check-if-an-objects-type-is-a-particular-subclass-in-c/56977583#56977583

    float playSound(String soundName)
    {
        return SoundPlayer.playSoundByName(soundName, BuckeyContext::currentLanguage);
    };
};
#endif