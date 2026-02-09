#include "lcd_ui.h"
#include "globals.h"

// Inicializa el LCD
void lcd_ui_setup(LCD_Handle *handle)
{
    lcd_driver_init(handle, LCD_ADDR, LCD_COLS, LCD_ROWS);
}

// Limpia la pantalla
void lcd_ui_clear(LCD_Handle *handle)
{
    lcd_driver_clear(handle);
}

// Mueve el cursor del LCD
void lcd_ui_setCursor(LCD_Handle *handle, uint8_t col, uint8_t row)
{
    lcd_driver_setCursor(handle, col, row);
}

// Enciende la luz de fondo
void lcd_ui_backlightOn(LCD_Handle *handle)
{
    lcd_driver_backlightOn(handle);
}

// Apaga la luz de fondo
void lcd_ui_backlightOff(LCD_Handle *handle)
{
    lcd_driver_backlightOff(handle);
}