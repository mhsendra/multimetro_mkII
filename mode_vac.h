#ifndef MODE_VAC_H
#define MODE_VAC_H

#include "config.h"   // aquí está el enum VacSubMode

extern VacSubMode vacSubMode;

float measureVAC();
float measureVAC_Relative();

void showVAC();
void showVAC_Relative();

void measureVAC_MODE();

#endif
