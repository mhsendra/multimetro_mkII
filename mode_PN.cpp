#include "mode_pn.h"
#include "lcd_ui.h"
#include "config.h"
#include "mode_diode.h"

// Submodos PN
#include "mode_transistor.h" // showTransistor()
#include "mode_mosfet.h"     // showMosfet()
#include "mode_zener.h"      // mode_zener_run()

// Variable global del submodo (debes tenerla en otro módulo)
extern DiodeSubMode diodeSubMode;

// =====================================================
// DISPATCHER DEL MODO PN
// =====================================================
void measurePN_MODE()
{
    switch (diodeSubMode)
    {
    case DIODE_MAIN:
        showDiode();
        break;

    case DIODE_TRANSISTOR:
        showTransistor();
        break;

    case DIODE_MOSFET:
        showMosfet();
        break;

    case DIODE_ZENER:
        mode_zener_run();
        break;
    }
}