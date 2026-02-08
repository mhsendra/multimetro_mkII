/*#include "adc.h"
#include <math.h>

void adc_setSPS(uint16_t sps)
{
    ads.setDataRate(sps);
}
// =====================================================
// LECTURA ADC (ADS1115)
// =====================================================

float readADC(uint8_t ch)
{
    return ads.readADC_SingleEnded(ch) * ADC_LSB;
}

float readADC_Pin(uint8_t pin)
{
    pinMode(pin, INPUT);
    int raw = analogRead(pin);
    return (raw * OHM_VREF) / 1023.0f;
}

float readADC_Average(uint8_t ch, uint16_t samples)
{
    float sum = 0;
    for (uint16_t i = 0; i < samples; i++)
        sum += readADC(ch);
    return sum / samples;
}

void initADC()
{
    ads.begin();
    ads.setGain(GAIN_ONE); // Ajusta según tu hardware
}

float readCurrent_mA()
{
    float v = readADC(ADC_IMA); // tensión medida en el amplificador
    float i = v / (SHUNT_MAIN_OHMS * SHUNT_GAIN);
    return i;
}
*/
#include <Arduino.h>

// Stub temporal mientras migramos todos los modos al ADC Manager
float readADC(uint8_t ch)
{
    // Devuelve 0 para que los modos antiguos sigan funcionando sin romper
    return 0.0f;
}

// ===============================
// STUBS TEMPORALES ADS1115
// ===============================
void initADC()
{
    // No hace nada, stub temporal
}
void adc_setSPS(unsigned int sps)
{
    // No hace nada, stub temporal
}
float readADC_Average(unsigned char ch, unsigned int samples)
{
    // Devuelve 0 para que los modos antiguos sigan funcionando return 0.0f;
}