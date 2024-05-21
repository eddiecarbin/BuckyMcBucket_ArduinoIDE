#include "ToggleSwitchMonitor.h"
#include <Arduino.h>

ToggleSwitchMonitor::ToggleSwitchMonitor(int pin)
{
    pinNumber = pin;
    pinMode(pinNumber, INPUT_PULLUP);

    int val = digitalRead(pinNumber);
    currentState = val;
}

bool ToggleSwitchMonitor::getState()
{
    return currentState;
}

bool ToggleSwitchMonitor::update()
{

    int val = digitalRead(pinNumber);

    if (currentState != val)
    {
        if (debounceCount++ >= 5)
        {
            currentState = val;
            debounceCount = 0;
            return true;
        }
    }
    return false;
}
