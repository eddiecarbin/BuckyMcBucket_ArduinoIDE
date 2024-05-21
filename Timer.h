#ifndef TIMER_h
#define TIMER_h

// https://forum.arduino.cc/t/simple-timer-library/483497/9

#include <Arduino.h>

class Timer
{

public:
    Timer(int);
    Timer();

    boolean isExpired();
    int setTimer(int);

private:
    unsigned long startTime = 0;
    unsigned long seconds = 0;
};

#endif
