#include <Arduino.h>
#include "JumpGesture.h"
#include "MotionController.h"

bool JumpGesture::calculateGesture(MotionController &controller)
{
    isInMotion = false;

    if (controller.getTotalAcceleration() > tolerance)
    {
        if (!delayStarted)
        {
            delayStarted = true;
            startTime = millis();
        }

        unsigned long elaspedTime = millis() - startTime;

        if (elaspedTime >= motionDelay)
        {
            isInMotion = true;
            delayStarted = false;
            // Serial.println("IN MOTION");
        }
    }
    else
    {
        delayStarted = false;
    }

    return isInMotion;
}