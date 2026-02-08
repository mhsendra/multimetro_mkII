#include "menus.h"

// =====================================================
// MENÚS
// =====================================================
void freqMenu() {
    lcd.clear();
    lcd.print("FREQ MENU");
    lcd.setCursor(0,1);

    switch (freqSubMode) {
        case FREQ_MAIN:        lcd.print("1) Frequency"); break;
        case FREQ_DUTY:        lcd.print("2) Duty"); break;
        case FREQ_PULSE_WIDTH: lcd.print("3) PulseWidth"); break;
        case FREQ_PERIOD:      lcd.print("4) Period"); break;
    }
}

void vdcMenu() {
    lcd.clear();
    lcd.print("VDC MENU");
    lcd.setCursor(0,1);

    switch (vdcSubMode) {
        case VDC_MAIN:        lcd.print("1) Voltage"); break;
        case VDC_POWER:       lcd.print("2) Power"); break;
        case VDC_ENERGY:      lcd.print("3) Energy"); break;
        case VDC_CURRENT_EST: lcd.print("4) Est Curr"); break;
        case VDC_REL:         lcd.print("5) Rel"); break;
    }
}

void vacMenu() {
    lcd.clear();
    lcd.print("VAC MENU");
    lcd.setCursor(0,1);

    switch (vacSubMode) {
        case VAC_MAIN: lcd.print("1) RMS"); break; 
        case VAC_REL: lcd.print("2) Rel"); break;
    }
}

void ohmMenu() {
    lcd.clear();
    lcd.print("OHM MENU");
    lcd.setCursor(0,1);

    switch (ohmSubMode) {
        case OHM_MAIN:   lcd.print("1) R"); break;
        case OHM_CONT:   lcd.print("2) Cont"); break;
        case OHM_REL:    lcd.print("3) Rel"); break;
        case OHM_MINMAX: lcd.print("4) Min/Max"); break;
        case OHM_CABLE:  lcd.print("5) Cable"); break;
    }
}

void diodeMenu() {
    lcd.clear();
    lcd.print("DIODE MENU");
    lcd.setCursor(0,1);

    switch (diodeSubMode) {
        case DIODE_MAIN:       lcd.print("1) Diodo"); break;
        case DIODE_TRANSISTOR: lcd.print("2) Trans"); break;
        case DIODE_MOSFET:     lcd.print("3) MOSFET"); break;
        case DIODE_ZENER:      lcd.print("4) Zener"); break;
        case DIODE_AUTO:       lcd.print("5) Auto"); break;
    }
}

int readSelector() {
    int b0 = digitalRead(pin.SEL0);
    int b1 = digitalRead(pin.SEL1);
    int b2 = digitalRead(pin.SEL2);

    int code = (b2 << 2) | (b1 << 1) | b0;
    return code;
}

// =====================================================
// ACTUALIZACIÓN DE SUBMODOS
// =====================================================
void updateFreqSubMode() {
    static bool lastState = HIGH;
    bool state = digitalRead(pin.PIN_CAL);

    if (lastState == HIGH && state == LOW) {
        freqSubMode = (FreqSubMode)((freqSubMode + 1) % 4);
        freqMenu();
        delay(250);
    }
    lastState = state;
}

void updateVdcSubMode() {
    static bool lastState = HIGH;
    bool state = digitalRead(pin.PIN_CAL);

    if (lastState == HIGH && state == LOW) {
        vdcSubMode = (VdcSubMode)((vdcSubMode + 1) % 5);
        vdcMenu();
        delay(250);
    }
    lastState = state;
}

void updateVacSubMode() {
    static bool lastState = HIGH;
    bool state = digitalRead(pin.PIN_CAL);

    if (lastState == HIGH && state == LOW) {
        vacSubMode = (VacSubMode)((vacSubMode + 1) % 2);
        vacMenu();
        delay(250);
    }
    lastState = state;
}

void updateOhmSubMode() {
    static bool lastState = HIGH;
    bool state = digitalRead(pin.PIN_CAL);

    if (lastState == HIGH && state == LOW) {
        ohmSubMode = (OhmSubMode)((ohmSubMode + 1) % 5);
        ohmMenu();
        delay(250);
    }
    lastState = state;
}

void updateDiodeSubMode() {
    static bool lastState = HIGH;
    bool state = digitalRead(pin.PIN_CAL);

    if (lastState == HIGH && state == LOW) {
        diodeSubMode = (DiodeSubMode)((diodeSubMode + 1) % 5);
        diodeMenu();
        delay(250);
    }
    lastState = state;
}