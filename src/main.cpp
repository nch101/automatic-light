#include <avr/sleep.h>
#include <Arduino.h>

extern "C" {
  #include "config.h"
  #include "motion_detect.h"
}

direction_t                 DetectedMotion_State;

static int8_t               NumsOfPeople;

/*****************************************************************************
 * ProgramName: DetectedMotionStateUpdate
 * Description: 
 * Parameters:  None
 * Return:      None
 ****************************************************************************/
void DetectedMotionStateUpdate() {
  static uint32_t           preMillis = 0;

  switch (DetectedMotion_State) {
    case OUT:
      if (Check_MotionSensors()->sensor_in == DETECTED) {
        DetectedMotion_State = MAYBE_IN;
        preMillis = millis();
      };
      break;
    case MAYBE_IN:
      if (millis() - preMillis >= TIME_DELAY) {
        DetectedMotion_State = OUT;
      };

      if (Check_MotionSensors()->sensor_out == DETECTED) {
        DetectedMotion_State = IN;
        NumsOfPeople++;
      };
      break;
    case IN:
      if (Check_MotionSensors()->sensor_out == DETECTED) {
        DetectedMotion_State = MAYBE_OUT;
        preMillis = millis();
      };
      break;
    case MAYBE_OUT:
      if (millis() - preMillis >= TIME_DELAY) {
        DetectedMotion_State = IN;
      };

      if (Check_MotionSensors()->sensor_in == DETECTED) {
        DetectedMotion_State = OUT;
        NumsOfPeople--;
      };
      break;
    default:
      break;
  };
};

void sleeping() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_mode();
};

void setup() {
  NumsOfPeople                      = 0;
  DetectedMotion_State              = OUT;
  Init_MotionSensors();
};

void loop() {
  DetectedMotionStateUpdate();
};

