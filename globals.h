#ifndef GLOBALS_H
#define GLOBALS_H

#include "pins.h"
#include "config.h"
#include <Adafruit_ADS1X15.h>
#include <LiquidCrystal_I2C.h>
#include "filters.h"
#include "lcd_driver.h"
#include <PCF8574.h>
#include "io_expander_pcf8574.h"

#define PCF8574_ADDR 0x20 // o 0x38 segun modelo
#define LCD_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

// === Pines ===
extern Pins pin; // Struct de pines

// === PCF8574 ===
extern PCF8574Expander pcf8574;

extern float ohmMax;
extern float ohmMin;

// Handle global del LCD
extern LCD_Handle lcd;

// === Filtros ===
extern Butterworth2 bw_vdc;
extern Butterworth2 bw_vac;
extern Butterworth2 bw_current;

// Filtros IIR para cada canal
extern float filter_vdc;     // filtro IIR para VDC
extern float filter_current; // filtro IIR para corriente
extern float filter_vac;     // filtro IIR para VAC, RMS deslizante
extern float filter_ohm;
extern float filter_continuity;
extern const float filter_alpha; // suavizado IIR (0 < alpha < 1)

// Inicialización de filtros
void initFilters();

// === Modos y submodos ===
extern MainMode selectedMode;
extern DiodeSubMode diodeSubMode;
extern CapSubMode capSubMode;
extern FreqSubMode freqSubMode;
extern OhmSubMode ohmSubMode;
extern VdcSubMode vdcSubMode;
extern VacSubMode vacSubMode;
extern OhmRange currentOhmRange;
extern CurrentRange currentRange;

#include "io_expander.h"

class IOExpander;

// Instancia global del expansor I2C
extern IOExpander *ioExpander;

// === Rango VDC ===
extern float vdc_ranges[3];
extern int vdc_range;
extern float acsOffset;

// VAC RMS deslizante
extern float vac_rms_accum;
extern const float vac_rms_alpha; // suavidad del filtro IIR

// === Calibración ===
extern Calibration cal;

// === Cable test ===
extern bool cableOK;
extern unsigned long lastBreak;

// === Backlight ===
extern unsigned long lastActivityTime;
extern unsigned long lastBacklightActivity;
extern bool backlightOff;

// === Medidas y referencias ===
extern float vdcRef;
extern float ohmRef;
extern float ohmMin;
extern float ohmMax;

// === ADC ===
extern Adafruit_ADS1115 ads;
extern uint16_t ads_mux;
extern uint16_t ads_gain;
extern uint16_t ads_sps;

#endif