#include "MotionGesture.h"
#include <Arduino.h>
#include "MotionController.h"

bool MotionGesture::calculateGesture(MotionController &controller)
{

    // Serial.print(" Acceleration: ");
    // Serial.print(controller.getTotalAcceleration());
    // Serial.print(" Gyro: ");
    // Serial.println(controller.getTotalGyro());
    // Serial.println(" ---------------------");

    if (controller.getTotalGyro() > gyroTolerance)
    {

        if (!isInMotion)
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
                // Serial.println("IN MOTIZON");
            }
        }
        else
        {
            delayStarted = false;
        }
    }
    else
    {
        if (isInMotion)
        {
            if (!delayStarted)
            {
                delayStarted = true;
                startTime = millis();
            }

            unsigned long elaspedTime = millis() - startTime;

            if (elaspedTime >= stillDelay)
            {
                isInMotion = false;
                delayStarted = false;
                // Serial.println("STOPPED MOTION");
            }
        }
        else
        {
            delayStarted = false;
        }
    }

    return isInMotion;
}