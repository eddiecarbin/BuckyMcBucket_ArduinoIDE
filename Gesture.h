
#ifndef GESTURE_H__
#define GESTURE_H__

#include <Arduino.h>
#include "MotionController.h"

class Gesture
{

public:
    Gesture(){

    };
    virtual bool calculateGesture(MotionController &controller) = 0;
};

#endif