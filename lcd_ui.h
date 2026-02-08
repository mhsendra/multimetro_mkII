#ifndef LCD_UI_H
#define LCD_UI_H

#include <Arduino.h>

void lcd_ui_clear();
void lcd_ui_print(const char* text);
void lcd_ui_printFloat(float value, uint8_t decimals);
void lcd_ui_setCursor(uint8_t col, uint8_t row);

void lcd_ui_backlightOn();
void lcd_ui_backlightOff();

#endif
