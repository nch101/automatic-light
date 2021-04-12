#include "motion_detect.h"

static volatile motion_sensors_t MotionSensors;

/*****************************************************************************
 * ProgramName: SensorInChange
 * Description: Interrupt callback function when sensor in is changing
 * Parameters:  None
 * Return:      None
 ****************************************************************************/
void SensorInChange() {
  delay(50);
  MotionSensors.sensor_in = digitalRead(SENSOR_IN_PIN) ? NOT_DETECTED : DETECTED;
};

/*****************************************************************************
 * ProgramName: CheckSensorOut
 * Description: 
 * Parameters:  None
 * Return:      None
 ****************************************************************************/
static void CheckSensorOut() {
  delay(50);
  MotionSensors.sensor_out = digitalRead(SENSOR_OUT_PIN) ? NOT_DETECTED : DETECTED;
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

  attachInterrupt(pinToISR(SENSOR_IN_PIN), SensorInChange, CHANGE);
};

/*****************************************************************************
 * ProgramName: Chech_MotionSensors
 * Description: Get motion sensors data struct
 * Parameters:  None
 * Return:      motion_sensors_t*
 ****************************************************************************/
motion_sensors_t* volatile Check_MotionSensors() {
  CheckSensorOut();
  return &MotionSensors;
};