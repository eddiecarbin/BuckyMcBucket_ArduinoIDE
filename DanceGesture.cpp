#include <Arduino.h>
#include "DanceGesture.h"
#include "MotionController.h"

bool DanceGesture::calculateGesture(MotionController &controller)
{
    isInMotion = false;

    if (controller.getTotalAcceleration() > tolerance || controller.getTotalGyro() > gyroTolerance)
    {
        if (!delayStarted)
        {
            failedCount = 0;
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

        failedCount += 1;
        if (failedCount == 3)
        {
            delayStarted = false;
        }
    }

    return isInMotion;
}