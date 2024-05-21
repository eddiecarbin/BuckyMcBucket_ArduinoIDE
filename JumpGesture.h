
#ifndef JUMPGESTURE_H__
#define JUMPGESTURE_H__

#include <Arduino.h>
#include "MotionController.h"
#include "Gesture.h"

class JumpGesture : public Gesture
{

private:
    double tolerance = 1.8;
    bool delayStarted = false;
    unsigned long startTime = 0;
    unsigned long endTime = 0;

    bool isInMotion = false;
    unsigned int motionDelay = 1300;

public:
    JumpGesture(){

    };

    virtual ~JumpGesture(){};

    bool calculateGesture(MotionController &controller) override;
};

#endif