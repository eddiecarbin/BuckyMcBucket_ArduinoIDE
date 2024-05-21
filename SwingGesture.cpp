#include "SwingGesture.h"
#include <Arduino.h>
#include "MotionController.h"

bool SwingGesture::calculateGesture(MotionController &controller)
{
    isInMotion = false;

    if (controller.getTotalAcceleration() > tolerance || controller.getTotalGyro() > tolerance)
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