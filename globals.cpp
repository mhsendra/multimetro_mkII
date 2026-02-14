#include "globals.h"

// === Pines ===
Pins pin;

// === PCF8574 ===
PCF8574Expander pcf8574(PCF8574_ADDR);
IOExpander *ioExpander = &pcf8574; // **definición real**

// Definición del LCD global
LCD_Handle lcd;

// Instancias de filtros
Butterworth2 bw_vdc;
Butterworth2 bw_vac;
Butterworth2 bw_current;

// Estados de EMA/IIR
float filter_vdc = -1e9; // valor inicial muy bajo para detectar primera medición
float filter_vac = -1e9;
float filter_current = -1e9;
float filter_ohm = -1e9;
float filter_continuity = -1e9;
const float filter_alpha = 0.05f;

// Inicialización de filtros
void initFilters();

// === Modos y submodos ===
MainMode selectedMode = MODE_VDC;
DiodeSubMode diodeSubMode = DIODE_MAIN;
CapSubMode capSubMode = CAP_RANGE_UF;
FreqSubMode freqSubMode = FREQ_MAIN;
OhmSubMode ohmSubMode = OHM_MAIN;
VdcSubMode vdcSubMode = VDC_MAIN;
VacSubMode vacSubMode = VAC_MAIN;
OhmRange currentOhmRange = OHM_RANGE_MID;
CurrentRange currentRange = CURR_RANGE_mA;

// === Rango VDC ===
float vdc_ranges[3] = {2.0f, 20.0f, 200.0f};
int vdc_range = 0;
float acsOffset = 0.0f;

// Inicialización de VAC RMS
float vac_rms_accum = 0.0f;
const float vac_rms_alpha = 0.05f; // ajustar según suavidad deseada

// === Calibración ===
Calibration cal;

// === Cable test ===
bool cableOK = false;
unsigned long lastBreak = 0;

// === Backlight ===
unsigned long lastActivityTime = 0;
unsigned long lastBacklightActivity = 0;
bool backlightOff = false;

// === Medidas y referencias ===
float vdcRef = 0.0f;
float ohmRef = NAN;
float ohmMin = 0.0f;
float ohmMax = 0.0f;

// === ADC ===
Adafruit_ADS1115 ads;
uint16_t ads_mux = 0;
uint16_t ads_gain = 0;
uint16_t ads_sps = 0;