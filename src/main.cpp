#include <avr/sleep.h>
#include <avr/power.h>
#include <Arduino.h>

extern "C" {
  #include "config.h"
  #include "motion_detect.h"
  #include "light.h"
  #include "fan.h"
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
  #ifdef DEBUG
  Serial.println("Begin sleeping");
  #endif //DEBUG
  delay(WAKEUP_DELAY);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_mode();
  #ifdef DEBUG
  Serial.println("Wakeup");
  #endif //DEBUG
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
    SystemState = STANDBY;
    #ifdef DEBUG
    Serial.println("STANDBY");
    #endif //DEBUG
    preMillis = millis();
    break;

  case STANDBY:
    if (millis() - preMillis >= TIME_DELAY) {
      SystemState = SLEEPING;
      #ifdef DEBUG
      Serial.println("SLEEPING");
      #endif //DEBUG
    };

    if ((NumsOfPeople > 0 && *Check_LightState() == OFF) || *Check_FanState() == ON) {
      SystemState = WORKING;
      #ifdef DEBUG
      Serial.println("WORKING");
      #endif //DEBUG
      TurnOn_Light();
    };
    break;

  case WORKING:
    if (NumsOfPeople == 0) {
      TurnOff_Light();
    };
    if (*Check_FanState() == OFF && *Check_LightState() == OFF) {
      #ifdef DEBUG
      Serial.println("SLEEPING");
      #endif //DEBUG
      SystemState = SLEEPING;
    };

    NumsOfPeople = NumsOfPeople < 0 ? 0 : NumsOfPeople;
    break;

  default:
    break;
  }
};

void setup() {
  power_adc_disable();
  power_spi_disable();
  power_twi_disable();
  power_timer1_disable();
  power_timer2_disable();

  NumsOfPeople                      = 0;
  DetectedMotionState               = NONE;
  SystemState                       = SLEEPING;
  Init_MotionSensors();
  Init_Light();
  Init_Fan();

  #ifdef DEBUG
  Serial.begin(BAUDRATE_DEFAULT);
  Serial.println("Running...");
  #endif // DEBUG
};

void loop() {
  SystemStateUpdate();
  DetectedMotionStateUpdate();

  #ifdef DEBUG
  Serial.println("***************");
  Serial.print(" People: ");
  Serial.println(NumsOfPeople);
  Serial.print(" Motion: ");
  Serial.println(DetectedMotionState);
  Serial.print(" SystemState: ");
  Serial.println(SystemState);
  Serial.print(" FanState: ");
  Serial.println(*Check_FanState());
  Serial.print(" LightState: ");
  Serial.println(*Check_LightState());
  Serial.println("***************");
  #endif // DEBUG

  delay(150);
};