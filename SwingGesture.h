
#ifndef SWINGGESTURE_H__
#define SWINGGESTURE_H__

#include <Arduino.h>
#include "MotionController.h"
#include "Gesture.h"

class SwingGesture : public Gesture
{

private:
    double tolerance = 0.8;
    bool delayStarted = false;
    unsigned long startTime = 0;
    unsigned long endTime = 0;

    bool isInMotion = false;
    unsigned int motionDelay = 2100;

public:
    SwingGesture(){

    };

    virtual ~SwingGesture(){};

    bool calculateGesture(MotionController &controller) override;
};

#endif