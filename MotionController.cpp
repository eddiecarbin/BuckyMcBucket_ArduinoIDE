#include "MotionController.h"

MotionController::MotionController()
{
}

void MotionController::update()
{

  if (IMU.accelerationAvailable())
  {

    float lx, ly, lz;
    IMU.readAcceleration(lx, ly, lz);
    // Serial.print(lx);
    // Serial.print('\t');
    // Serial.print(ly);
    // Serial.print('\t');
    // Serial.println(lz);

    // totalAcceleration = abs(lx) + abs(ly) + abs(lz);
    totalAcceleration = sqrt(lx * lx + ly * ly + lz * lz);
    // Serial.print("Total Accel: ");
    // Serial.println(totalAcceleration);
  }

  if (IMU.gyroscopeAvailable())
  {
    float gx, gy, gz;

    IMU.readGyroscope(gx, gy, gz);

    // Serial.print(gx);
    // Serial.print('\t');
    // Serial.print(gy);
    // Serial.print('\t');
    // Serial.println(gz);

    // totalGyro = abs(gx) + abs(gy) + abs(gz);
    totalGyro = sqrt(gx * gx + gy * gy + gz * gz);

    // Serial.println(totalGyro);
  }

  // float x, y, z;

  // if (IMU.magneticFieldAvailable())
  // {
  //   IMU.readMagneticField(x, y, z);

  //   Serial.print(x);
  //   Serial.print('\t');
  //   Serial.print(y);
  //   Serial.print('\t');
  //   Serial.println(z);

  //   double totalMag = sqrt(x * x + y * y + z * z);
  //   Serial.print("Total Mag: ");
  //   Serial.println(totalMag);
  // }
}

double MotionController::getTotalAcceleration()
{
  return totalAcceleration;
}

double MotionController::getTotalGyro()
{
  return totalGyro;
}
// Path: BuckeyContext.cpp