
#ifndef __NOTIONCONTROLLER_H__
#define __NOTIONCONTROLLER_H__

#include <Arduino.h>
#include <Arduino_BMI270_BMM150.h>

class MotionController
{
private:
    // float lx = 0;
    // float ly = 0;
    // float lz = 0;

    // float gx = 0;
    // float gy = 0;
    // float gz = 0;

    double totalAcceleration = 0;
    double totalGyro = 0;
    // double mx = 0;
    // double my = 0;
    // double mz = 0;

    // double ox = 0;
    // double oy = 0;
    // double oz = 0;

public:
    MotionController();

    double getTotalAcceleration();

    double getTotalGyro();

    void update();
};

#endif