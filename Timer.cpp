#include "Timer.h"
#include <Arduino.h>

Timer::Timer(int aSeconds)
{
    setTimer(aSeconds);
}

Timer::Timer()
{
}

int Timer::setTimer(int aSeconds)
{
    seconds = aSeconds;
    startTime = millis();

    return aSeconds;
}

boolean Timer::isExpired()
{
    if (millis() - startTime >= seconds * 1000)
    {
        return true;
    }
    return false;
}
