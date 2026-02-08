#include "selector.h"
#include "globals.h"

#include "mode_vdc.h"
#include "mode_vac.h"
#include "mode_ohm.h"
#include "mode_current.h"
#include "mode_cap.h"
#include "mode_freq.h"
#include "induct.h"
#include "mode_diode.h"

void runCurrentMode()
{
    switch (currentMode)
    {

    case MODE_VDC:         // Posición 0
        measureVDC_MODE(); // Dispatcher real de VDC
        break;

    case MODE_VAC:         // Posición 1
        measureVAC_MODE(); // Dispatcher real de VAC
        break;

    case MODE_OHM_CONT: // Posición 2
        measureOHM_MODE();   // Dispatcher real del modo ohm
        break;

    case MODE_DIODE_TRANS:   // Posición 3
        measureDiode_main(); // Dispatcher real del modo diodo
        break;

    case MODE_CURR_mA: // Posición 4
        currentRange = CURR_RANGE_mA;
        measureCURRENT(); // Dispatcher real de corriente
        break;

    case MODE_CURR_A: // Posición 5
        currentRange = CURR_RANGE_5A;
        measureCURRENT(); // Dispatcher real de corriente
        break;

    case MODE_CAP:    // Posición 6
        measureCAPMode(); // Dispatcher real de capacitancia
        break;

    case MODE_L:             // Posición 7
        measureInductance(); // Dispatcher real de inductancia
        break;

    default:
        break;
    }
}
