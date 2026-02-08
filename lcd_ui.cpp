#include "lcd_ui.h"
#include <LiquidCrystal_I2C.h>

// Declarado en otro módulo (normalmente main .ino o lcd_setup.cpp)
extern LiquidCrystal_I2C lcd;

// =====================================================
// FUNCIONES BÁSICAS DE UI
// =====================================================

void lcd_ui_clear() {
    lcd.clear();
}

void lcd_ui_print(const char* text) {
    lcd.print(text);
}

void lcd_ui_printFloat(float value, uint8_t decimals) {
    lcd.print(value, decimals);
}

void lcd_ui_setCursor(uint8_t col, uint8_t row) {
    lcd.setCursor(col, row);
}

// =====================================================
// BACKLIGHT
// =====================================================

void lcd_ui_backlightOn() {
    lcd.backlight();
}

void lcd_ui_backlightOff() {
    lcd.noBacklight();
}