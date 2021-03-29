#ifndef FAN_H
#define FAN_H

#include <Arduino.h>
#include "config.h"

void Init_Fan();

void TurnOn_Fan();
void TurnOff_Fan();

state_t* Check_FanState();

#endif // FAN_H