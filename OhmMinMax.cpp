#include "OhmMinMax.h"
#include "lcd_ui.h"
#include "mode_ohm.h"

static float ohmMin = INFINITY;
static float ohmMax = 0;

void ohmMinMax_reset() {
    ohmMin = INFINITY;
    ohmMax = 0;
}

void ohmMinMax_update(float R) {
    if (R < ohmMin) ohmMin = R;
    if (R > ohmMax) ohmMax = R;
}

void ohmMinMax_show() { 
    lcd_ui_clear(); 
    lcd_ui_print("MIN:"); 
    lcd_ui_printFloat(ohmMin, 1); 
    lcd_ui_setCursor(0, 1); 
    lcd_ui_print("MAX:"); 
    lcd_ui_printFloat(ohmMax, 1); 
    }