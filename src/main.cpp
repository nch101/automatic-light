#include <Arduino.h>
extern "C" {
  #include "config.h"
  #include "motion_detect.h"
}

motion_direct_t       personState;
light_state_t         lightState;

static uint32_t       preMillis;
static int8_t         numOfPeople;

void personStateUpdate() {
  switch (personState) {
    case OUT:
      if (motionDirectDetect() == MAYBE_IN) {
        //change person detect state to maybe has people
        personState = MAYBE_IN;

        //set timeout
        preMillis = millis();
      };
      break;
    case MAYBE_IN:
      if (millis() - preMillis >= TIME_DELAY) {
        personState = OUT;
      };

      if (motionDirectDetect() == IN) {
        personState = IN;
        numOfPeople++;
      };
      break;
    case IN:
      if (motionDirectDetect()  ==  MAYBE_OUT) {
        personState = MAYBE_OUT;

        //set timeout
        preMillis = millis();
      };
      break;
    case MAYBE_OUT:
      if (millis() - preMillis >= TIME_DELAY) {
        personState = IN;
      };

      if (motionDirectDetect() == OUT) {
        personState = OUT;
        numOfPeople--;
      };
      break;
    default:
      break;
  };
};

void setup() {
  initMotionSensors();
}

void loop() {
  personStateUpdate();

  if (numOfPeople > 0 && lightState == LIGHT_OFF) {
    //turn on the light

  } else if (numOfPeople == 0 && lightState == LIGHT_ON) {
    //turn off the light
    
  } else {
    numOfPeople = 0;
  };
};

