#ifndef MODE_CURRENT_H
#define MODE_CURRENT_H

#include <Arduino.h>
#include "config.h"

// Lecturas por rango (A)
float measureCurrent_mA();
float measureCurrent_5A();
float measureCurrent_16A();

// Lectura unificada según currentRange (A)
float measureCURRENT_calibrated();

// Pantalla y modo
void showCURRENT();
void measureCURRENT();

#endif