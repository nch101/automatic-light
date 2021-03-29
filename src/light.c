#include "light.h"

static state_t        LightState;

/*****************************************************************************
 * ProgramName: Init_Light
 * Description: Initial pinMode and set LightState = OFF
 * Parameters:  None
 * Return:      None
 ****************************************************************************/
void Init_Light() {
  pinMode(LIGHT_PIN, OUTPUT);
  LightState                        = OFF;
}

/*****************************************************************************
 * ProgramName: TurnOn_Light
 * Description: Set LIGHT_PIN to HIGH and update LightState = ON
 * Parameters:  None
 * Return:      None
 ****************************************************************************/
void TurnOn_Light() {
  digitalWrite(LIGHT_PIN, HIGH);
  LightState                        = ON;
}

/*****************************************************************************
 * ProgramName: TurnOff_Light
 * Description: Set LIGHT_PIN to LOW and update LightState = OFF
 * Parameters:  None
 * Return:      None
 ****************************************************************************/
void TurnOff_Light() {
  digitalWrite(LIGHT_PIN, LOW);
  LightState                        = OFF;
}

/*****************************************************************************
 * ProgramName: Check_LightState
 * Description: Get light state
 * Parameters:  None
 * Return:      light_state_t*
 ****************************************************************************/
state_t* Check_LightState() {
  return &LightState;
}