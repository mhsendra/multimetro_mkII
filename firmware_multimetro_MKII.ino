#include "config.h"
#include "globals.h"
#include "filters.h"
#include "globals.h"
#include "lcd_ui.h"
#include "lcd_driver.h"
#include "menus.h"
#include "calibration.h"
#include "adcmanager.h"
#include "mode_vdc.h"
#include "mode_vac.h"
#include "mode_ohm.h"
#include "mode_current.h"
#include "mode_cap.h"
#include "mode_freq.h"
#include "mode_diode.h"
#include "mode_zener.h"
#include "induct.h"
#include "backlight.h"
#include "mode_dispatchers.h"
#include "selector.h"
#include "io_expander_pcf8574.h"
// #include "io_expander_mcp23017.h"

// Temporizador global
unsigned long lastUpdate = 0;
const unsigned long updateInterval = 20; // 20 ms → 50 Hz

void setup()
{
    // ---- PCF8574 ----
    // PCF8574Expander pcf8574(0x20);
    // IOExpander *ioExpander = &pcf8574;

    // Configurar pines del selector como entrada en el expansor
    ioExpander->pinMode(pin.SEL0, INPUT);
    ioExpander->pinMode(pin.SEL1, INPUT);
    ioExpander->pinMode(pin.SEL2, INPUT);

    // Inicializar LCD
    lcd_driver_init(&lcd, LCD_ADDR, LCD_COLS, LCD_ROWS);
    pinMode(pin.BOOST_HV_CTRL, OUTPUT);
    digitalWrite(pin.BOOST_HV_CTRL, HIGH); // modo seguro → 5V

    backlight_reset();

    // Inicialización de hardware
    Wire.begin();
    lcd_ui_setup(&lcd);

    // Inicialización de pines
    pinMode(pin.PIN_CAL, INPUT_PULLUP);
    pinMode(pin.PIN_BUZZER, OUTPUT);
    pinMode(pin.SEL0, INPUT_PULLUP);
    pinMode(pin.SEL1, INPUT_PULLUP);
    pinMode(pin.SEL2, INPUT_PULLUP);

    // Inicialización de módulos
    loadCalibration();
    initFilters();
    adc_manager_init();

    // Mensaje de bienvenida en pantalla
    lcd_ui_clear(&lcd);
    lcd_driver_print(&lcd, "Multímetro");
}

void loop()
{
    unsigned long now = millis();
    if (now - lastUpdate >= updateInterval)
    {
        lastUpdate = now;

        // 1️⃣ Leer selector físico y actualizar selectedMode inmediatamente
        int sel = readSelector(ioExpander);
        switch (sel)
        {
        case 0:
            selectedMode = MODE_VDC;
            break;
        case 1:
            selectedMode = MODE_VAC;
            break;
        case 2:
            selectedMode = MODE_OHM;
            break;
        case 3:
            selectedMode = MODE_PN;
            break;
        case 4:
            selectedMode = MODE_CURRENT;
            currentRange = CURR_RANGE_mA;
            break;
        case 5:
            selectedMode = MODE_CURRENT;
            currentRange = CURR_RANGE_5A;
            break;
        case 6:
            selectedMode = MODE_CAP;
            break;
        case 7:
            selectedMode = MODE_INDUCT;
            break;
        default:
            selectedMode = MODE_VDC;
            break;
        }

        // 2️⃣ Ejecutar el modo actualizado
        dispatchMode(selectedMode);

        // 3️⃣ Actualización de sistemas auxiliares
        backlight_update();
    }
    // 4️⃣ Aquí se pueden poner tareas muy rápidas no críticas
}