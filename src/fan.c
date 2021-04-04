#include "fan.h"

static state_t FanState;

/*****************************************************************************
 * ProgramName: FanControlChange
 * Description: Interrupt callback function when fan button is pressed
 * Parameters:  None
 * Return:      None
 ****************************************************************************/
void FanControlChange() {
  delay(50);
  FanState == OFF ? TurnOn_Fan() : TurnOff_Fan();
};

/*****************************************************************************
 * ProgramName: Init_Fan
 * Description: Initial pinMode and set FanState = OFF
 * Parameters:  None
 * Return:      None
 ****************************************************************************/
void Init_Fan() {
  pinMode(FAN_PIN, OUTPUT);
  pinMode(FAN_CONTROL_PIN, INPUT_PULLUP);

  attachInterrupt(pinToISR(FAN_CONTROL_PIN), FanControlChange, FALLING);
  
  FanState                          = OFF;
  digitalWrite(FAN_PIN, LOW);
};

/*****************************************************************************
 * ProgramName: TurnOn_Fan
 * Description: Set FAN_PIN to HIGH and update FanState = ON
 * Parameters:  None
 * Return:      None
 ****************************************************************************/
void TurnOn_Fan() {
  digitalWrite(FAN_PIN, HIGH);
  FanState                          = ON;
};

/*****************************************************************************
 * ProgramName: TurnOff_Fan
 * Description: Set FAN_PIN to LOW and update FanState = OFF
 * Parameters:  None
 * Return:      None
 ****************************************************************************/
void TurnOff_Fan() {
  digitalWrite(FAN_PIN, LOW);
  FanState                          = OFF;
};

/*****************************************************************************
 * ProgramName: Check_FanState
 * Description: Get fan state
 * Parameters:  None
 * Return:      state_t*
 ****************************************************************************/
state_t* Check_FanState() {
  return &FanState;
};