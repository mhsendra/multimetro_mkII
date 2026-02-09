#include <Arduino.h>
#include "CableTest.h"
#include "mode_ohm.h"
#include "lcd_ui.h"
#include "auto_hold.h"
#include "backlight.h"
#include "autoOff.h"
#include "range_control.h"
#include "globals.h"
#include "config.h"

// Umbral para considerar cable OK
static constexpr float CABLE_MAX_R = 5.0f;

/* =====================================================
 * MEDICIÓN DE CABLE (usa modo OHM)
 * ===================================================== */
float measureCable()
{
    // Medición de resistencia del cable
    float R = measureOhmValue();

    if (R < 0 || isnan(R))
        return NAN;

    return R;
}

/* =====================================================
 * PANTALLA
 * ===================================================== */
void showCable()
{
    // Reset de sistemas auxiliares
    backlight_activity();
    autoHold_reset();
    autoOff_reset();

    lcd_ui_clear(&lcd);
    lcd_driver_print(&lcd, "Detectando...");
    delay(200);

    float R = measureCable();

    // Registrar actividad
    if (!isnan(R))
    {
        backlight_activity();
        autoOff_activity();
    }

    // --- AUTO HOLD ---
    if (autoHold_update(R))
    {
        float held = autoHold_getHeldValue();

        lcd_ui_clear(&lcd);
        lcd_driver_print(&lcd, "CABLE (HOLD)");
        lcd_ui_setCursor(&lcd, 0, 1);

        if (isnan(held))
        {
            lcd_driver_print(&lcd, "ERROR");
            return;
        }

        if (held <= CABLE_MAX_R)
        {
            lcd_driver_print(&lcd, "OK  (");
            lcd_driver_printFloat(&lcd, held, 2);
            lcd_driver_print(&lcd, " Ohm)");
        }
        else
        {
            lcd_driver_print(&lcd, "BREAK (");
            lcd_driver_printFloat(&lcd, held, 2);
            lcd_driver_print(&lcd, " Ohm)");
        }
        return;
    }

    // --- Lectura normal ---
    lcd_ui_clear(&lcd);
    lcd_driver_print(&lcd, "CABLE");
    lcd_ui_setCursor(&lcd, 0, 1);

    if (isnan(R))
    {
        lcd_driver_print(&lcd, "ERROR");
        return;
    }

    if (R <= CABLE_MAX_R)
    {
        lcd_driver_print(&lcd, "OK  (");
        lcd_driver_printFloat(&lcd, R, 2);
        lcd_driver_print(&lcd, " Ohm)");
    }
    else
    {
        lcd_driver_print(&lcd, "BREAK (");
        lcd_driver_printFloat(&lcd, R, 2);
        lcd_driver_print(&lcd, " Ohm)");
    }
}

/* =====================================================
 * API PÚBLICA DEL MODO CABLE
 * ===================================================== */
void measureCableMode()
{
    showCable();
}