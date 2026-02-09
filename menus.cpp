#include "menus.h"
#include "lcd_ui.h"

// =====================================================
// MENÚS
// =====================================================
void freqMenu()
{
    lcd_driver_clear(&lcd);
    lcd_driver_print(&lcd, "FREQ MENU");
    lcd_ui_setCursor(&lcd, 0, 1);

    switch (freqSubMode)
    {
    case FREQ_MAIN:
        lcd_driver_print(&lcd, "1) Frequency");
        break;
    case FREQ_DUTY:
        lcd_driver_print(&lcd, "2) Duty");
        break;
    case FREQ_PULSE_WIDTH:
        lcd_driver_print(&lcd, "3) PulseWidth");
        break;
    case FREQ_PERIOD:
        lcd_driver_print(&lcd, "4) Period");
        break;
    }
}

void vdcMenu()
{
    lcd_driver_clear(&lcd);
    lcd_driver_print(&lcd, "VDC MENU");
    lcd_ui_setCursor(&lcd, 0, 1);

    switch (vdcSubMode)
    {
    case VDC_MAIN:
        lcd_driver_print(&lcd, "1) Voltage");
        break;
    case VDC_POWER:
        lcd_driver_print(&lcd, "2) Power");
        break;
    case VDC_ENERGY:
        lcd_driver_print(&lcd, "3) Energy");
        break;
    case VDC_CURRENT_EST:
        lcd_driver_print(&lcd, "4) Est Curr");
        break;
    case VDC_REL:
        lcd_driver_print(&lcd, "5) Rel");
        break;
    }
}

void vacMenu()
{
    lcd_driver_clear(&lcd);
    lcd_driver_print(&lcd, "VAC MENU");
    lcd_driver_setCursor(&lcd, 0, 1);

    switch (vacSubMode)
    {
    case VAC_MAIN:
        lcd_driver_print(&lcd, "1) RMS");
        break;
    case VAC_REL:
        lcd_driver_print(&lcd, "2) Rel");
        break;
    }
}

void ohmMenu()
{
    lcd_driver_clear(&lcd);
    lcd_driver_print(&lcd, "OHM MENU");
    lcd_driver_setCursor(&lcd, 0, 1);

    switch (ohmSubMode)
    {
    case OHM_MAIN:
        lcd_driver_print(&lcd, "1) R");
        break;
    case OHM_CONT:
        lcd_driver_print(&lcd, "2) Cont");
        break;
    case OHM_REL:
        lcd_driver_print(&lcd, "3) Rel");
        break;
    case OHM_MINMAX:
        lcd_driver_print(&lcd, "4) Min/Max");
        break;
    case OHM_CABLE:
        lcd_driver_print(&lcd, "5) Cable");
        break;
    }
}

void diodeMenu()
{
    lcd_driver_clear(&lcd);
    lcd_driver_print(&lcd, "DIODE MENU");
    lcd_driver_setCursor(&lcd, 0, 1);

    switch (diodeSubMode)
    {
    case DIODE_MAIN:
        lcd_driver_print(&lcd, "1) Diodo");
        break;
    case DIODE_TRANSISTOR:
        lcd_driver_print(&lcd, "2) Trans");
        break;
    case DIODE_MOSFET:
        lcd_driver_print(&lcd, "3) MOSFET");
        break;
    case DIODE_ZENER:
        lcd_driver_print(&lcd, "4) Zener");
        break;
    case DIODE_AUTO:
        lcd_driver_print(&lcd, "5) Auto");
        break;
    }
}

int readSelector()
{
    int b0 = digitalRead(pin.SEL0);
    int b1 = digitalRead(pin.SEL1);
    int b2 = digitalRead(pin.SEL2);

    int code = (b2 << 2) | (b1 << 1) | b0;
    return code;
}

// =====================================================
// ACTUALIZACIÓN DE SUBMODOS
// =====================================================
void updateFreqSubMode()
{
    static bool lastState = HIGH;
    bool state = digitalRead(pin.PIN_CAL);

    if (lastState == HIGH && state == LOW)
    {
        freqSubMode = (FreqSubMode)((freqSubMode + 1) % 4);
        freqMenu();
        delay(250);
    }
    lastState = state;
}

void updateVdcSubMode()
{
    static bool lastState = HIGH;
    bool state = digitalRead(pin.PIN_CAL);

    if (lastState == HIGH && state == LOW)
    {
        vdcSubMode = (VdcSubMode)((vdcSubMode + 1) % 5);
        vdcMenu();
        delay(250);
    }
    lastState = state;
}

void updateVacSubMode()
{
    static bool lastState = HIGH;
    bool state = digitalRead(pin.PIN_CAL);

    if (lastState == HIGH && state == LOW)
    {
        vacSubMode = (VacSubMode)((vacSubMode + 1) % 2);
        vacMenu();
        delay(250);
    }
    lastState = state;
}

void updateOhmSubMode()
{
    static bool lastState = HIGH;
    bool state = digitalRead(pin.PIN_CAL);

    if (lastState == HIGH && state == LOW)
    {
        ohmSubMode = (OhmSubMode)((ohmSubMode + 1) % 5);
        ohmMenu();
        delay(250);
    }
    lastState = state;
}

void updateDiodeSubMode()
{
    static bool lastState = HIGH;
    bool state = digitalRead(pin.PIN_CAL);

    if (lastState == HIGH && state == LOW)
    {
        diodeSubMode = (DiodeSubMode)((diodeSubMode + 1) % 5);
        diodeMenu();
        delay(250);
    }
    lastState = state;
}