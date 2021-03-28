#include "motion_detect.h"

static sensor_t motion_sensor;

void sensor_in_rising() {
  motion_sensor.sensor_in = MOVING;
};

void sensor_out_rising() {
  motion_sensor.sensor_out = MOVING;
}

void sensor_in_falling() {
  motion_sensor.sensor_in = NOT_MOVING;
}

void sensor_out_falling() {
  motion_sensor.sensor_out = NOT_MOVING;
}

void initMotionSensors() {
  pinMode(SENSOR_IN_PIN, INPUT_PULLUP);
  pinMode(SENSOR_OUT_PIN, INPUT_PULLUP);

  attachInterrupt(pinToISR(SENSOR_IN_PIN), sensor_in_rising, RISING);
  attachInterrupt(pinToISR(SENSOR_IN_PIN), sensor_in_falling, FALLING);

  attachInterrupt(pinToISR(SENSOR_OUT_PIN), sensor_out_rising, RISING);
  attachInterrupt(pinToISR(SENSOR_OUT_PIN), sensor_out_falling, FALLING);
}

motion_direct_t motionDirectDetect() {
  if (motion_sensor.sensor_in == MOVING && motion_sensor.sensor_out == NOT_MOVING) {
    return MAYBE_IN;
  } else if (motion_sensor.sensor_in == MOVING && motion_sensor.sensor_out == MOVING) {
    if (personState == MAYBE_IN) {
      return IN;
    } else if (personState == MAYBE_OUT) {
      return OUT;
    };
  } else if (motion_sensor.sensor_in == NOT_MOVING && motion_sensor.sensor_out == MOVING) {
    return MAYBE_OUT;
  };
  
  return UNKNOWN;
};
