#ifndef MOTION_DETECT_H
#define MOTION_DETECT_H

#include <Arduino.h>
#include "config.h"

#define           SENSOR_IN_PIN           6
#define           SENSOR_OUT_PIN          7

#define           pinToISR(x)             digitalPinToInterrupt(x)

void Init_MotionSensors();

void SensorInRising();
void SensorOutRising();
void SensorInFalling();
void SensorOutFalling();

motion_sensors_t* Check_MotionSensors();

#endif // MOTION_DETECT_H