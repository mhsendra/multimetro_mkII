#ifndef LCD_SETUP_H
#define LCD_SETUP_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

// Instancia global del LCD
extern LiquidCrystal_I2C lcd;

// Inicialización del LCD
void lcd_setup();

#endif
