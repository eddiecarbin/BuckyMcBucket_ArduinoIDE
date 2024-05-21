
#ifndef MOTIONGESTURE_H__
#define MOTIONGESTURE_H__

#include <Arduino.h>
#include "MotionController.h"
#include "Gesture.h"

class MotionGesture : public Gesture
{

private:
    double tolerance = 2.8;
    double  gyroTolerance = 20.0;

    bool delayStarted = false;
    unsigned long startTime = 0;
    unsigned long endTime = 0;

    bool isInMotion = false;
    unsigned int motionDelay = 1100;
    unsigned int stillDelay = 2000;

public:
    MotionGesture(){

    };

    virtual ~MotionGesture()
    {
    }
    bool calculateGesture(MotionController &controller) override;
};

#endif