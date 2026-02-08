#include "cap_utils.h"
#include "adc.h"
#include "pins.h"
#include "config.h"

// =====================================================
// DESCARGA DEL CONDENSADOR
// =====================================================
void dischargeCap() {
    pinMode(pin.CAP_CHARGE_PIN, OUTPUT);
    digitalWrite(pin.CAP_CHARGE_PIN, LOW);
    delay(CAP_DISCHARGE_MS);
}

// =====================================================
// PROTECCIÓN POR VOLTAJE RESIDUAL
// =====================================================
bool prepareCapMeasurement() {
    float v = readADC_Average(CAP_ADC_CH, 10);
    if (v > CAP_RESIDUAL_VOLT_MAX)
        return false;

    dischargeCap();
    return true;
}