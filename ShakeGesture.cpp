#include "ShakeGesture.h"
#include <Arduino.h>
#include "MotionController.h"

bool ShakeGesture::calculateGesture(MotionController &controller)
{
    isInMotion = false;

    // Serial.print(" Acceleration: ");
    // Serial.print(controller.getTotalAcceleration());
    // Serial.print(" Gyro: ");
    // Serial.println(controller.getTotalGyro());
    // Serial.println(" ---------------------");

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
            Serial.println("Successfill Shake");
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