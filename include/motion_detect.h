#ifndef MOTION_DETECT_H
#define MOTION_DETECT_H

#include <Arduino.h>
#include "config.h"

#define         SENSOR_IN_PIN           6
#define         SENSOR_OUT_PIN          7

#define         pinToISR(x)             digitalPinToInterrupt(x)

extern motion_direct_t      personState;

typedef enum {
  NOT_MOVING,
  MOVING
} motion_sensor_state_t;

typedef struct {
  motion_sensor_state_t sensor_in;
  motion_sensor_state_t sensor_out;
} sensor_t;

void initMotionSensors();

void sensor_in_rising();
void sensor_out_rising();
void sensor_in_falling();
void sensor_out_falling();

motion_direct_t motionDirectDetect();

#endif // MOTION_DETECT_H