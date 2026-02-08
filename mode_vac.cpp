#include "mode_vac.h"
#include "adcmanager.h"
#include "globals.h"
#include "lcd_ui.h"
#include "config.h"
#include <math.h>
#include "auto_Hold.h"
#include "AutoOff.h"
#include "backlight.h"
#include "range_control.h"

// =====================================================
// CONFIGURACIÓN VAC
// =====================================================
#define VAC_SAMPLES 256

// =====================================================
// VAC — RAW (sin calibrar)
// =====================================================
float measureVAC_raw(void)
{
    const int N = VAC_SAMPLES;
    float sumSq = 0.0f;

    for (int i = 0; i < N; i++)
    {
        // Leer voltaje directamente del ADS1115
        float v = adc_manager_read_voltage();

        // Protección por saturación
        if (fabs(v) > 4.95f)
            return INFINITY;

        sumSq += v * v;
    }

    float rms = sqrtf(sumSq / N);

    // Escalado según rango AC
    float scale = 1.0f;
    switch (adc_manager_current_range())
    {
    case RANGE_AC_2V:
        scale = 0.011f;
        break;
    case RANGE_AC_20V:
        scale = 0.110f;
        break;
    case RANGE_AC_200V:
        scale = 1.10f;
        break;
    default:
        return NAN;
    }

    return rms * scale;
}

// =====================================================
// VAC — CALIBRADO
// =====================================================
float measureVAC_calibrated(void)
{
    float v = measureVAC_raw();
    if (isinf(v))
        return v;

    return v * cal.vac;
}

// =====================================================
// VAC RELATIVO
// =====================================================
static float vac_reference = NAN;

float measureVAC_Relative(void)
{
    float v = measureVAC_calibrated();
    if (isnan(vac_reference))
        vac_reference = v;

    return v - vac_reference;
}

// =====================================================
// AUTO-RANGO VISUAL (mV / V) con histéresis
// =====================================================
static bool use_millivolts_vac(float v)
{
    static bool in_mV = false;

    if (v < 0.95f)
        in_mV = true;
    if (v > 1.05f)
        in_mV = false;

    return in_mV;
}

// =====================================================
// PANTALLAS
// =====================================================
void showVAC(void)
{
    float v = measureVAC_calibrated();
    if (autoHold_update(v))
        v = autoHold_getHeldValue();

    lcd_ui_clear();

    if (isinf(v))
    {
        lcd_ui_print("VAC: OVL");
        return;
    }

    if (use_millivolts_vac(v))
    {
        lcd_ui_print("VAC: ");
        lcd_ui_printFloat(v * 1000.0f, 1);
        lcd_ui_print(" mV");
    }
    else
    {
        lcd_ui_print("VAC: ");
        lcd_ui_printFloat(v, 3);
        lcd_ui_print(" V");
    }
}

void showVAC_Relative(void)
{
    float v = measureVAC_Relative();
    lcd_ui_clear();

    if (isinf(v))
    {
        lcd_ui_print("REL AC: OVL");
        return;
    }

    if (use_millivolts_vac(fabs(v)))
    {
        lcd_ui_print("REL AC: ");
        lcd_ui_printFloat(v * 1000.0f, 1);
        lcd_ui_print(" mV");
    }
    else
    {
        lcd_ui_print("REL AC: ");
        lcd_ui_printFloat(v, 3);
        lcd_ui_print(" V");
    }
}

// =====================================================
// MODO COMPLETO VAC
// =====================================================
void measureVAC_MODE(void)
{
    // Liberar pines RNGx si se venían usando en modo OHM
    rng_release_for_gpio();

    // Actividad de usuario
    backlight_activity();
    autoOff_activity();

    // Configurar velocidad del ADC
    adc_manager_set_sps(ADC_SPS_250);

    // Selección de rango inicial (puede mejorarse con auto-rango)
    adc_manager_select(RANGE_AC_20V);

    switch (vacSubMode)
    {
    case VAC_MAIN:
    {
        float v = measureVAC_calibrated();

        if (autoHold_update(v))
            v = autoHold_getHeldValue();

        showVAC();
        break;
    }

    case VAC_REL:
        showVAC_Relative();
        break;
    }
}