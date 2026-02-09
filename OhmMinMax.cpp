#include "OhmMinMax.h"
#include "lcd_ui.h"
#include "mode_ohm.h"
#include "globals.h"

void ohmMinMax_reset()
{
    ohmMin = INFINITY;
    ohmMax = 0;
}

void ohmMinMax_update(float R)
{
    if (R < ohmMin)
        ohmMin = R;
    if (R > ohmMax)
        ohmMax = R;
}

void ohmMinMax_show()
{
    lcd_ui_clear(&lcd);
    lcd_driver_print(&lcd, "MIN:");
    lcd_driver_printFloat(&lcd, ohmMin, 1);
    lcd_ui_setCursor(&lcd, 0, 1);
    lcd_driver_print(&lcd, "MAX:");
    lcd_driver_printFloat(&lcd, ohmMax, 1);
}