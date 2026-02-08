#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void lcd_setup() {
    lcd.begin(16, 2);
    lcd.backlight();
}