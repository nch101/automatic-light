#ifndef LIGHT_H
#define LIGHT_H

#include <Arduino.h>
#include "config.h"

void Init_Light();

void TurnOn_Light();
void TurnOff_Light();

light_state_t* Check_LightState();

#endif // LIGHT_H