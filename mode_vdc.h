#ifndef MODE_VDC_H
#define MODE_VDC_H

#include "config.h"   // Aquí está la enum VdcSubMode

// Solo declaramos la variable, NO la enum
extern VdcSubMode vdcSubMode;

// Prototipos
float measureVDC();
float measureVDC_Relative();
float measurePower();
float measureEnergy();

void showVDC();
void showVDC_Relative();
void showPower();
void showEnergy();

void measureVDC_MODE();

#endif