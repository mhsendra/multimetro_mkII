#ifndef MENUS_H
#define MENUS_H

#include <Arduino.h>
#include "globals.h"

int readSelector();

// Menús de submodos
void freqMenu();
void vdcMenu();
void vacMenu();
void ohmMenu();
void diodeMenu();

// Actualización de submodos
void updateFreqSubMode();
void updateVdcSubMode();
void updateVacSubMode();
void updateOhmSubMode();
void updateDiodeSubMode();

#endif