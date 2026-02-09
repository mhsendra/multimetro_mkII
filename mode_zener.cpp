#include <Arduino.h>
#include "mode_zener.h"
#include "adcmanager.h"
#include "lcd_ui.h"
#include "auto_hold.h"
#include "backlight.h"
#include "autoOff.h"
#include "globals.h"
#include "range_control.h"
#include "config.h"

/* =====================================================
 * MEDIR DIODO ZENER
 * ===================================================== */
float measureZener()
{
    rng_release_for_gpio(); // liberar RNG para este modo

    // Preparar pines
    pinMode(pin.TP1, OUTPUT);
    digitalWrite(pin.TP1, HIGH); // corriente de prueba
    pinMode(pin.TP2, INPUT);

    adc_manager_select(RANGE_DC_20V);
    adc_manager_set_sps(ADC_SPS_475);

    delay(10); // estabilizar

    float vz = adc_manager_read_voltage();

    // Saturación por protección
    if (vz > 4.95f)
        vz = 4.95f;

    // Reset de pines
    pinMode(pin.TP1, INPUT);
    pinMode(pin.TP2, INPUT);

    if (vz < 0.1f) // muy bajo, no detectado
        return NAN;

    return vz;
}

/* =====================================================
 * PANTALLA
 * ===================================================== */
void mode_zener_run()
{
    // Reset de sistemas auxiliares
    backlight_activity();
    autoHold_reset();
    autoOff_reset();

    lcd_ui_clear(&lcd);
    lcd_driver_print(&lcd, "Detectando Zener...");
    delay(200);

    float vz = measureZener();

    if (!isnan(vz))
    {
        backlight_activity();
        autoOff_activity();
    }

    // --- AUTO HOLD ---
    if (autoHold_update(vz))
    {
        float held = autoHold_getHeldValue();

        lcd_ui_clear(&lcd);
        lcd_driver_print(&lcd, "ZENER (HOLD)");
        lcd_ui_setCursor(&lcd, 0, 1);

        if (isnan(held))
        {
            lcd_driver_print(&lcd, "OL");
            return;
        }

        lcd_driver_print(&lcd, "Vz:");
        lcd_driver_printFloat(&lcd, held, 2);
        lcd_driver_print(&lcd, " V");
        return;
    }

    // --- Lectura normal ---
    lcd_ui_clear(&lcd);
    lcd_driver_print(&lcd, "ZENER");
    lcd_ui_setCursor(&lcd, 0, 1);

    if (isnan(vz))
    {
        lcd_driver_print(&lcd, "OL");
        return;
    }

    lcd_driver_print(&lcd, "Vz:");
    lcd_driver_printFloat(&lcd, vz, 2);
    lcd_driver_print(&lcd, " V");
}