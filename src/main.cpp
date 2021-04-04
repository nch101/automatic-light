#include <avr/sleep.h>
#include <Arduino.h>

extern "C" {
  #include "config.h"
  #include "motion_detect.h"
  #include "light.h"
}

system_state_t              SystemState;
static direction_t          DetectedMotionState;
static int8_t               NumsOfPeople;
static uint32_t             preMillis;

/*****************************************************************************
 * ProgramName: sleeping
 * Description: 
 * Parameters:  None
 * Return:      None
 ****************************************************************************/
static void sleeping() {
  delay(WAKEUP_DELAY);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_mode();
  delay(WAKEUP_DELAY);
};

/*****************************************************************************
 * ProgramName: DetectedMotionStateUpdate
 * Description: 
 * Parameters:  None
 * Return:      None
 ****************************************************************************/
static void DetectedMotionStateUpdate() {
  switch (DetectedMotionState) {
    case NONE:
      if (Check_MotionSensors()->sensor_in == DETECTED) {
        DetectedMotionState = MAYBE_IN;
        preMillis = millis();
      };

      if (Check_MotionSensors()->sensor_out == DETECTED) {
        DetectedMotionState = MAYBE_OUT;
        preMillis = millis();
      };
      break;
    case MAYBE_IN:
      if (millis() - preMillis >= TIME_DELAY) {
        DetectedMotionState = NONE;
      };

      if (Check_MotionSensors()->sensor_out == DETECTED) {
        DetectedMotionState = IN;
        NumsOfPeople++;
      };
      break;
    case IN:
      if (Check_MotionSensors()->sensor_out == NOT_DETECTED) {
        DetectedMotionState = NONE;
      };
      break;
    case MAYBE_OUT:
      if (millis() - preMillis >= TIME_DELAY) {
        DetectedMotionState = NONE;
      };

      if (Check_MotionSensors()->sensor_in == DETECTED) {
        DetectedMotionState = OUT;
        NumsOfPeople--;
      };
      break;
    case OUT:
      if (Check_MotionSensors()->sensor_in == NOT_DETECTED) {
        DetectedMotionState = NONE;
      };
      break;
    default:
      break;
  };
};

/*****************************************************************************
 * ProgramName: SystemStateUpdate
 * Description: 
 * Parameters:  None
 * Return:      None
 ****************************************************************************/
static void SystemStateUpdate() {
  switch (SystemState) {
  case SLEEPING:
    sleeping();
    DetectedMotionState = MAYBE_IN;
    SystemState = STANDBY;
    preMillis = millis();
    break;
  case STANDBY:
    if (NumsOfPeople > 0 && *Check_LightState() == OFF) {
      SystemState = WORKING;
      TurnOn_Light();
    }

    if (millis() - preMillis >= TIME_DELAY) {
      SystemState = SLEEPING;
    }

    if (NumsOfPeople < 0) {
      NumsOfPeople = 0;
      SystemState = SLEEPING;
    }
    break;
  case WORKING:
    if (NumsOfPeople == 0) {
      SystemState = SLEEPING;
      TurnOff_Light();
    }
    break;
  default:
    break;
  }
};

void setup() {
  NumsOfPeople                      = 0;
  DetectedMotionState               = NONE;
  SystemState                       = SLEEPING;
  Init_MotionSensors();
  Init_Light();

  #ifdef DEBUG
  Serial.begin(BAUDRATE_DEFAULT);
  Serial.println("Sleeping...");
  #endif // DEBUG
};

void loop() {
  SystemStateUpdate();
  DetectedMotionStateUpdate();

  #ifdef DEBUG
  Serial.println("***********");
  Serial.print(" People: ");
  Serial.println(NumsOfPeople);
  Serial.print(" State: ");
  Serial.println(SystemState);
  Serial.print(" Motion: ");
  Serial.println(DetectedMotionState);
  Serial.println("***********");
  #endif // DEBUG

  delay(150);
};