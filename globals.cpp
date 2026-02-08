#include "globals.h"
#include "filters.h"
#include "pins.h"
#include <Adafruit_ADS1X15.h>
#include <LiquidCrystal_I2C.h>
float vdc_ranges[3] = {2.0f, 20.0f, 200.0f};
int vdc_range = 0;

float acsOffset = 0.0f;

// ===============================
// DEFINICIÓN DE VARIABLES GLOBALES
// ===============================

// Pines
Pins pin;

// Calibración
Calibration cal;

// ADC ADS1115
Adafruit_ADS1115 ads;

// Rangos
OhmRange currentOhmRange = OHM_RANGE_MID;
CurrentRange currentRange = CURR_RANGE_mA;
CapSubMode capSubMode = CAP_RANGE_UF;
DiodeSubMode diodeSubMode = DIODE_MAIN;
VdcSubMode vdcSubMode = VDC_MAIN;
VacSubMode vacSubMode = VAC_MAIN;

// Auto-off y backlight
unsigned long lastActivityTime = 0;
unsigned long lastBacklightActivity = 0;
bool autoOffActive = true;
bool backlightOff = false;

// Submodo OHM por defecto
OhmSubMode ohmSubMode = OHM_MAIN;
// Valor de referencia para modo REL
float ohmRef = NAN;