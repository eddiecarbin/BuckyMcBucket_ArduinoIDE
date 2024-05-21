
#ifndef DANCEGESTURE_H__
#define DANCEGESTURE_H__

#include <Arduino.h>
#include "MotionController.h"
#include "Gesture.h"

class DanceGesture : public Gesture
{

private:
    double tolerance = 2.0;
    double gyroTolerance = 50.0;
    bool delayStarted = false;
    unsigned long startTime = 0;
    unsigned long endTime = 0;

    unsigned int failedCount = 0;
    bool isInMotion = false;
    unsigned int motionDelay = 2000;

public:
    DanceGesture(){

    };

    virtual ~DanceGesture(){};

    bool calculateGesture(MotionController &controller) override;
};

#endif