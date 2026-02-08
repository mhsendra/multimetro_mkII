#include "calibration.h"
#include "adc.h"
#include "mode_vac.h"
#include "mode_ohm.h"
#include "mode_current.h"
#include "mode_freq.h"
#include "induct.h"
#include <EEPROM.h>

// =====================================================
// CARGAR CALIBRACIÓN
// =====================================================
void loadCalibration() {
    EEPROM.get(0, cal);

    if (isnan(cal.vdc)) {
        cal.vdc = 1.0;
        cal.vac = 1.0;
        cal.ohm = 1.0;

        cal.curr_shunt_gain = 1.0;
        cal.curr_shunt_offset = 0.0;

        cal.acs_offset = 2.5;
        cal.acs_sens = 0.185; // valor típico ACS712-05B
    }
}

void calibrateVDC() {
    lcd.clear();
    lcd.print("VDC: aplicar 5.00V");
    lcd.setCursor(0,1);
    lcd.print("OK=CAL");
    while (digitalRead(pin.PIN_CAL) == HIGH);
    delay(300);

    float v_meas = readADC_Average(ADC_VOLT, 200);
    cal.vdc = 5.00 / v_meas;
}

void calibrateOHM() {
    lcd.clear();
    lcd.print("OHM: conectar 1k");
    lcd.setCursor(0,1);
    lcd.print("OK=CAL");
    while (digitalRead(pin.PIN_CAL) == HIGH);
    delay(300);

    float r_meas = measureOhmValue();
    cal.ohm = 1000.0 / r_meas;
}

void calibrateVAC() {
    lcd.clear();
    lcd.print("VAC: aplicar 230 V");
    lcd.setCursor(0,1);
    lcd.print("OK=CAL");
    while (digitalRead(pin.PIN_CAL) == HIGH);
    delay(300);

}

void calibrateCurrent_mA() {

    lcd.clear();
    lcd.print("I mA: 0mA");
    lcd.setCursor(0,1);
    lcd.print("OK=CAL");
    while (digitalRead(pin.PIN_CAL) == HIGH);
    delay(300);

    // Offset del amplificador
    cal.curr_shunt_offset = readADC_Average(ADC_IMA, 200);

    lcd.clear();
    lcd.print("I mA: 100mA");
    lcd.setCursor(0,1);
    lcd.print("OK=CAL");
    while (digitalRead(pin.PIN_CAL) == HIGH);
    delay(300);

    float v_load = readADC_Average(ADC_IMA, 200);
    float I_real = 0.100; // 100mA exactos

    cal.curr_shunt_gain = I_real / (v_load - cal.curr_shunt_offset);
}

void calibrateCurrent_5A() {

    lcd.clear();
    lcd.print("I 5A: aplicar 5A");
    lcd.setCursor(0,1);
    lcd.print("OK=CAL");
    while (digitalRead(pin.PIN_CAL) == HIGH);
    delay(300);

    float v_load = readADC_Average(ADC_IMA, 200);
    float I_real = 5.00;

    cal.curr_shunt_gain = I_real / (v_load - cal.curr_shunt_offset);
}

void calibrateCurrent_16A() {

    lcd.clear();
    lcd.print("ACS: 0A");
    lcd.setCursor(0,1);
    lcd.print("OK=CAL");
    while (digitalRead(pin.PIN_CAL) == HIGH);
    delay(300);

    cal.acs_offset = readADC_Average(ADC_ACS, 200);

    lcd.clear();
    lcd.print("ACS: 10A");
    lcd.setCursor(0,1);
    lcd.print("OK=CAL");
    while (digitalRead(pin.PIN_CAL) == HIGH);
    delay(300);

    float v_load = readADC_Average(ADC_ACS, 200);
    float I_real = 10.0;

    cal.acs_sens = (v_load - cal.acs_offset) / I_real;
}

void calibrateESR() {

    lcd.clear();
    lcd.print("ESR: corto");
    lcd.setCursor(0,1);
    lcd.print("OK=CAL");
    while (digitalRead(pin.PIN_CAL) == HIGH);
    delay(300);

    float i0 = readCurrent_mA();
    if (i0 < 0.00001f) i0 = 0.00001f;

    cal.esr_factor = 5.0 / i0;
}

void calibrateFrequency() {

    lcd.clear();
    lcd.print("FREQ: 1kHz");
    lcd.setCursor(0,1);
    lcd.print("OK=CAL");
    while (digitalRead(pin.PIN_CAL) == HIGH);
    delay(300);

    float f_meas = measureFrequency_calibrated();
    if (f_meas < 1) f_meas = 1;

    cal.freq_factor = 1000.0 / f_meas;
}

void calibrateInductance() {

    lcd.clear();
    lcd.print("IND: 1mH");
    lcd.setCursor(0,1);
    lcd.print("OK=CAL");
    while (digitalRead(pin.PIN_CAL) == HIGH);
    delay(300);

    float L_meas = measureInductancePulse();
    if (L_meas < 0.000001f) L_meas = 0.000001f;

    cal.induct_factor = 0.001 / L_meas;
}

// =====================================================
// MODO CALIBRACIÓN COMPLETO
// =====================================================
void enterCalibration() {
    lcd.clear();
    lcd.print("CALIBRACION");
    delay(1500);

    // ============================
    // 1) OFFSET ADC (0V)
    // ============================
    lcd.clear();
    lcd.print("1) Desconectar");
    lcd.setCursor(0,1);
    lcd.print("entradas. OK=CAL");
    while (digitalRead(pin.PIN_CAL) == HIGH);
    delay(300);

    float offset = readADC_Average(ADC_VOLT, 200);

    cal.vdc = 1.0;
    cal.vac = 1.0;
    cal.ohm = 1.0;
    //cal.ima = 1.0;
    //cal.ia  = 1.0;
    //cal.acsOffset = readADC_Average(ADC_ACS, 200);
    cal.acs_offset = readADC_Average(ADC_ACS, 200);
    // ============================
    // 2) VDC (5.00V exactos)
    // ============================
    lcd.clear();
    lcd.print("2) Aplicar 5.00V");
    lcd.setCursor(0,1);
    lcd.print("OK=CAL");
    while (digitalRead(pin.PIN_CAL) == HIGH);
    delay(300);

    float v_meas = readADC_Average(ADC_VOLT, 200);
    cal.vdc = 5.00 / v_meas;

    // ============================
    // 3) VAC (50/60 Hz)
    // ============================
    lcd.clear();
    lcd.print("3) Aplicar VAC");
    lcd.setCursor(0,1);
    lcd.print("OK=CAL");
    while (digitalRead(pin.PIN_CAL) == HIGH);
    delay(300);

    float vac_meas = measureVAC();
    cal.vac = 230.0 / vac_meas;

    // ============================
    // 4) OHMIOS (1k exacto)
    // ============================
    lcd.clear();
    lcd.print("4) Conectar 1k");
    lcd.setCursor(0,1);
    lcd.print("OK=CAL");
    while (digitalRead(pin.PIN_CAL) == HIGH);
    delay(300);

    float r_meas = measureOhmValue();
    cal.ohm = 1000.0 / r_meas;

    // ============================
    // 5) CORRIENTE mA (100mA)
    // ============================
    lcd.clear(); 
    lcd.print("5) 100mA"); 
    lcd.setCursor(0,1); 
    lcd.print("OK=CAL"); 
    while (digitalRead(pin.PIN_CAL) == HIGH); 
    delay(300); 
    // Offset del amplificador 
    cal.curr_shunt_offset = readADC_Average(ADC_IMA, 200);
    // Medida con corriente real 
    float v_load = readADC_Average(ADC_IMA, 200); 
    float I_real_mA = 0.100; // 100mA exactos 
    cal.curr_shunt_gain = I_real_mA / (v_load - cal.curr_shunt_offset);

    // ============================
    // 6) CORRIENTE 5A
    // ============================
    lcd.clear(); 
    lcd.print("6) 5.00A"); 
    lcd.setCursor(0,1); 
    lcd.print("OK=CAL"); 
    while (digitalRead(pin.PIN_CAL) == HIGH); 
    delay(300); 
    float v_load2 = readADC_Average(ADC_IMA, 200); 
    float I_real_5A = 5.00; 
    cal.curr_shunt_gain = I_real_5A / (v_load2 - cal.curr_shunt_offset);

    // ============================
    // 7) CORRIENTE 16A (ACS712)
    // ============================
    lcd.clear(); 
    lcd.print("7) ACS 0A"); 
    lcd.setCursor(0,1); 
    lcd.print("OK=CAL"); 
    while (digitalRead(pin.PIN_CAL) == HIGH); 
    delay(300); // Offset ACS 
    cal.acs_offset = readADC_Average(ADC_ACS, 200); 
    lcd.clear(); 
    lcd.print("Aplicar 10A"); 
    lcd.setCursor(0,1); 
    lcd.print("OK=CAL"); 
    while (digitalRead(pin.PIN_CAL) == HIGH); 
    delay(300); 
    float v_acs = readADC_Average(ADC_ACS, 200); 
    float I_real_acs = 10.0; 
    cal.acs_sens = (v_acs - cal.acs_offset) / I_real_acs;

    // ============================
    // 8) ESR
    // ============================
    lcd.clear();
    lcd.print("7) ESR: Corto");
    lcd.setCursor(0,1);
    lcd.print("OK=CAL");
    while (digitalRead(pin.PIN_CAL) == HIGH);
    delay(300);

    float i0 = readCurrent_mA();
    if (i0 < 0.00001f) i0 = 0.00001f;
    cal.esr_factor = 5.0 / i0;

    // ============================
    // 9) FRECUENCIA (1kHz)
    // ============================
    lcd.clear();
    lcd.print("8) Aplicar 1kHz");
    lcd.setCursor(0,1);
    lcd.print("OK=CAL");
    while (digitalRead(pin.PIN_CAL) == HIGH);
    delay(300);

    float f_meas = measureFrequency_calibrated();
    if (f_meas < 1) f_meas = 1;
    cal.freq_factor = 1000.0 / f_meas;

    // ============================
    // 10) INDUCTANCIA (1mH)
    // ============================
    lcd.clear();
    lcd.print("IND: 1mH");
    lcd.setCursor(0,1);
    lcd.print("OK=CAL");
    while (digitalRead(pin.PIN_CAL) == HIGH);
    delay(300);

    float L_meas = measureInd_raw();
    if (L_meas < 0.000001f) L_meas = 0.000001f;

    cal.induct_factor = 0.001 / L_meas;   // 1 mH exacto

}

void calibrationMenu() {
    lcd.clear();
    lcd.print("CAL CURRENT");
    lcd.setCursor(0,1);
    lcd.print("1)mA  2)5A  3)16A");

    // ============================
    // GUARDAR EN EEPROM
    // ============================
    EEPROM.put(0, cal);

    lcd.clear();
    lcd.print("CAL COMPLETA");
    delay(2000);

    while (1);
}