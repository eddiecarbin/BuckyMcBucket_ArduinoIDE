#ifndef ToggleSwitchMonitor_h
#define ToggleSwitchMonitor_h

#include <Arduino.h>

class ToggleSwitchMonitor
{
private:
    int pinNumber = 0;
    bool currentState = 0;
    bool _intialised = false;
    int debounceCount = 0;

public:
    ToggleSwitchMonitor(int pin);
    bool getState();
    bool update();
};

#endif
