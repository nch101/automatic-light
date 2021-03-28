#include "light.h"

static light_state_t        LightState;

/*****************************************************************************
 * ProgramName: Init_Light
 * Description: Initial pinMode and set LightState = LIGHT_OFF
 * Parameters:  None
 * Return:      None
 ****************************************************************************/
void Init_Light() {
  pinMode(LIGHT_PIN, OUTPUT);
  LightState                        = LIGHT_OFF;
}

/*****************************************************************************
 * ProgramName: TurnOn_Light
 * Description: Set LIGHT_PIN to HIGH and update LightState = LIGHT_ON
 * Parameters:  None
 * Return:      None
 ****************************************************************************/
void TurnOn_Light() {
  digitalWrite(LIGHT_PIN, HIGH);
  LightState                        = LIGHT_ON;
}

/*****************************************************************************
 * ProgramName: TurnOff_Light
 * Description: Set LIGHT_PIN to LOW and update LightState = LIGHT_OFF
 * Parameters:  None
 * Return:      None
 ****************************************************************************/
void TurnOff_Light() {
  digitalWrite(LIGHT_PIN, LOW);
  LightState                        = LIGHT_OFF;
}

/*****************************************************************************
 * ProgramName: Check_LightState
 * Description: Get light state
 * Parameters:  None
 * Return:      light_state_t*
 ****************************************************************************/
light_state_t* Check_LightState() {
  return &LightState;
}