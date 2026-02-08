#include <Arduino.h>
#include "mode_zener.h"
#include "pcfwrapper.h"
#include "adcmanager.h"
#include "lcd_ui.h"
#include "auto_hold.h"
#include "backlight.h"
#include "autoOff.h"
#include "pins.h"
#include "range_control.h"
#include "config.h"

// =====================================================
// CONTROL AQY (inyecta corriente hacia TP1)
// =====================================================
static inline void zener_switch_on()
{
    uint8_t s = pcf_read();
    s |= pcf.ZENER_AQY;
    pcf_write(s);
}

static inline void zener_switch_off()
{
    uint8_t s = pcf_read();
    s &= ~pcf.ZENER_AQY;
    pcf_write(s);
}

/* =====================================================
 * MEDICIÓN ZENER
 * ===================================================== */
float measureZener()
{
    rng_release_for_gpio(); // liberar RNG para este modo

    // Encender AQY → corriente hacia TP1
    zener_switch_on();
    delay(5);

    // Seleccionar rango adecuado
    adc_manager_select(RANGE_DC_20V);
    adc_manager_set_sps(ADC_SPS_475);

    // Leer voltaje en TP1
    uint16_t raw = adc_manager_read_blocking();
    float vz = adc_manager_raw_to_voltage(raw);

    // Apagar AQY
    zener_switch_off();

    if (vz < 0.0f || isnan(vz))
        return NAN;

    return vz;
}

/* =====================================================
 * PANTALLA
 * ===================================================== */
void showZener()
{
    // Reset de sistemas auxiliares
    backlight_activity();
    autoHold_reset();
    autoOff_reset();

    lcd_ui_clear();
    lcd_ui_print("Detectando...");
    delay(200);

    float vz = measureZener();

    // Registrar actividad
    if (!isnan(vz))
    {
        backlight_activity();
        autoOff_activity();
    }

    // --- AUTO HOLD ---
    if (autoHold_update(vz))
    {
        float held = autoHold_getHeldValue();

        lcd_ui_clear();
        lcd_ui_print("ZENER (HOLD)");
        lcd_ui_setCursor(0, 1);

        if (isnan(held))
        {
            lcd_ui_print("OL");
            return;
        }

        lcd_ui_printFloat(held, 3);
        lcd_ui_print(" V");
        return;
    }

    // --- Lectura normal ---
    lcd_ui_clear();
    lcd_ui_print("ZENER");
    lcd_ui_setCursor(0, 1);

    if (isnan(vz))
    {
        lcd_ui_print("OL");
        return;
    }

    lcd_ui_printFloat(vz, 3);
    lcd_ui_print(" V");
}

/* =====================================================
 * API PÚBLICA DEL MODO ZENER
 * ===================================================== */
void measureZenerMode()
{
    showZener();
}