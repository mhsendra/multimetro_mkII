#ifndef GLOBALS_H
#define GLOBALS_H

#include "config.h"
#include "pins.h"
#include <Adafruit_ADS1X15.h>
#include <LiquidCrystal_I2C.h>
#include "filters.h"
extern Butterworth2 bw_vdc;
extern float vdc_ranges[3];
extern int vdc_range;
extern float acsOffset;
extern MeasureMode currentMode;
extern OhmRange currentOhmRange;
extern CurrentRange currentRange;
extern FreqSubMode freqSubMode;
extern VdcSubMode vdcSubMode;
extern VacSubMode vacSubMode;
extern OhmSubMode ohmSubMode;
extern DiodeSubMode diodeSubMode;
extern CapSubMode capSubMode;

extern float energy_Wh;
extern unsigned long lastEnergyTime;

extern float vdcRef;
extern float ohmRef;
extern float ohmMin;
extern float ohmMax;

extern bool cableOK;
extern unsigned long lastBreak;

extern Calibration cal;

extern Adafruit_ADS1115 ads;
extern LiquidCrystal_I2C lcd;

extern unsigned long lastActivityTime;
extern bool autoOffActive;

extern unsigned long lastBacklightActivity;
extern bool backlightOff;

extern unsigned long lastLcdUpdate;

void initFilters();

extern unsigned long lastBacklightActivity;
extern bool backlightOff;
extern Pins pin;
extern PCF pcf;

#define ADS1115_ADDR 0x48

#define ADS_OS_SINGLE 0x8000
#define ADS_MODE_SINGLE 0x0100
#define ADS_COMP_QUE_DISABLE 0x0003

// MUX (se rellenará según tu tabla)
extern uint16_t ads_mux;

// PGA (según rango)
extern uint16_t ads_gain;

// SPS (DR bits)
extern uint16_t ads_sps;

#endif
