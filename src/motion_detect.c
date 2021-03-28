#include "motion_detect.h"

static motion_sensors_t MotionSensors;

/*****************************************************************************
 * ProgramName: SensorInRising
 * Description: Interrupt callback function when sensor in is rising
 * Parameters:  None
 * Return:      None
 ****************************************************************************/
void SensorInRising() {
  MotionSensors.sensor_in = DETECTED;
};

/*****************************************************************************
 * ProgramName: SensorOutRising
 * Description: Interrupt callback function when sensor out is rising
 * Parameters:  None
 * Return:      None
 ****************************************************************************/
void SensorOutRising() {
  MotionSensors.sensor_out = DETECTED;
}

/*****************************************************************************
 * ProgramName: SensorInFalling
 * Description: Interrupt callback function when sensor in is falling
 * Parameters:  None
 * Return:      None
 ****************************************************************************/
void SensorInFalling() {
  MotionSensors.sensor_in = NOT_DETECTED;
}

/*****************************************************************************
 * ProgramName: SensorOutFalling
 * Description: Interrupt callback function when sensor out is falling
 * Parameters:  None
 * Return:      None
 ****************************************************************************/
void SensorOutFalling() {
  MotionSensors.sensor_out = NOT_DETECTED;
}

/*****************************************************************************
 * ProgramName: Init_MotionSensors
 * Description: Initial pinMode and attachInterrupt sensors pin
 * Parameters:  None
 * Return:      None
 ****************************************************************************/
void Init_MotionSensors() {
  pinMode(SENSOR_IN_PIN, INPUT_PULLUP);
  pinMode(SENSOR_OUT_PIN, INPUT_PULLUP);

  attachInterrupt(pinToISR(SENSOR_IN_PIN), SensorInRising, RISING);
  attachInterrupt(pinToISR(SENSOR_IN_PIN), SensorInFalling, FALLING);

  attachInterrupt(pinToISR(SENSOR_OUT_PIN), SensorOutRising, RISING);
  attachInterrupt(pinToISR(SENSOR_OUT_PIN), SensorOutFalling, FALLING);
}

/*****************************************************************************
 * ProgramName: Chech_MotionSensors
 * Description: Get motion sensors data struct
 * Parameters:  None
 * Return:      motion_sensors_t*
 ****************************************************************************/
motion_sensors_t* Check_MotionSensors() {
  return &MotionSensors;
}