#include <avr/sleep.h>
#include <Arduino.h>

extern "C" {
  #include "config.h"
  #include "motion_detect.h"
  #include "light.h"
}

static direction_t          DetectedMotionState;
static int8_t               NumsOfPeople;

/*****************************************************************************
 * ProgramName: DetectedMotionStateUpdate
 * Description: 
 * Parameters:  None
 * Return:      None
 ****************************************************************************/
static void DetectedMotionStateUpdate() {
  static uint32_t           preMillis = 0;

  switch (DetectedMotionState) {
    case OUT:
      if (Check_MotionSensors()->sensor_in == DETECTED) {
        DetectedMotionState = MAYBE_IN;
        preMillis = millis();
      };
      break;
    case MAYBE_IN:
      if (millis() - preMillis >= TIME_DELAY) {
        DetectedMotionState = OUT;
      };

      if (Check_MotionSensors()->sensor_out == DETECTED) {
        DetectedMotionState = IN;
        NumsOfPeople++;
      };
      break;
    case IN:
      if (Check_MotionSensors()->sensor_out == DETECTED) {
        DetectedMotionState = MAYBE_OUT;
        preMillis = millis();
      };
      break;
    case MAYBE_OUT:
      if (millis() - preMillis >= TIME_DELAY) {
        DetectedMotionState = IN;
      };

      if (Check_MotionSensors()->sensor_in == DETECTED) {
        DetectedMotionState = OUT;
        NumsOfPeople--;
      };
      break;
    default:
      break;
  };
};

/*****************************************************************************
 * ProgramName: LightStateUpdate
 * Description: 
 * Parameters:  None
 * Return:      None
 ****************************************************************************/
static void LightStateUpdate() {
  if (NumsOfPeople > 0 && *Check_LightState() == LIGHT_OFF) {
    TurnOn_Light();
  } else if (NumsOfPeople == 0 && *Check_LightState() == LIGHT_ON) {
    TurnOff_Light();
  };
};

/*****************************************************************************
 * ProgramName: sleeping
 * Description: 
 * Parameters:  None
 * Return:      None
 ****************************************************************************/
static void sleeping() {
  if (NumsOfPeople == 0 \
  && *Check_LightState() == LIGHT_OFF \
  && DetectedMotionState == OUT) {
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_mode();
    delay(WAKEUP_DELAY);
  }
};

void setup() {
  NumsOfPeople                      = 0;
  DetectedMotionState               = OUT;
  Init_MotionSensors();
  Init_Light();
};

void loop() {
  DetectedMotionStateUpdate();
  LightStateUpdate();
  sleeping();
};