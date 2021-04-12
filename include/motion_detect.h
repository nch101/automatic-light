#ifndef MOTION_DETECT_H
#define MOTION_DETECT_H

#include <Arduino.h>
#include "config.h"

void Init_MotionSensors();
motion_sensors_t* Check_MotionSensors();

#endif // MOTION_DETECT_H