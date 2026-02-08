#ifndef ADC_H
#define ADC_H

#include <Arduino.h>
#include <Adafruit_ADS1X15.h>
#include "globals.h"

// Instancia global del ADS1115
extern Adafruit_ADS1115 ads;

// Inicialización del ADC
void initADC();

void adc_setSPS(uint16_t sps);
// =====================================================
// FUNCIONES DE LECTURA ADC
// =====================================================

float readADC(uint8_t ch);
float readADC_Pin(uint8_t pin);
float readADC_Average(uint8_t ch, uint16_t samples);

// Medición de corriente (mA)
float readCurrent_mA();

#endif
