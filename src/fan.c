#include "fan.h"

static fan_state_t FanState;

/*****************************************************************************
 * ProgramName: FanControlRising
 * Description: Interrupt callback function when fan button is pressed
 * Parameters:  None
 * Return:      None
 ****************************************************************************/
void FanControlRising() {
  delay(100);
  FanState == FAN_OFF ? TurnOn_Fan() : TurnOff_Fan();
};

/*****************************************************************************
 * ProgramName: Init_Fan
 * Description: Initial pinMode and set FanState = FAN_OFF
 * Parameters:  None
 * Return:      None
 ****************************************************************************/
void Init_Fan() {
  pinMode(FAN_PIN, OUTPUT);
  pinMode(FAN_CONTROL_PIN, INPUT_PULLUP);

  attachInterrupt(pinToISR(FAN_CONTROL_PIN), FanControlRising, RISING);
  FanState                          = FAN_OFF;
};

/*****************************************************************************
 * ProgramName: TurnOn_Fan
 * Description: Set FAN_PIN to HIGH and update FanState = FAN_ON
 * Parameters:  None
 * Return:      None
 ****************************************************************************/
void TurnOn_Fan() {
  digitalWrite(FAN_PIN, HIGH);
  FanState                          = FAN_ON;
};

/*****************************************************************************
 * ProgramName: TurnOff_Fan
 * Description: Set FAN_PIN to LOW and update FanState = FAN_OFF
 * Parameters:  None
 * Return:      None
 ****************************************************************************/
void TurnOff_Fan() {
  digitalWrite(FAN_PIN, LOW);
  FanState                          = FAN_OFF;
};

/*****************************************************************************
 * ProgramName: Check_FanState
 * Description: Get fan state
 * Parameters:  None
 * Return:      fan_state_t*
 ****************************************************************************/
fan_state_t* Check_FanState() {
  return &FanState;
};