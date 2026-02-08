#include "OhmProtection.h"
#include "adc.h"
#include "config.h"

bool detectVoltageOnOhm() {
    return readADC_Average(ADC_OHM, 20) > OHM_PROTECT_THRESHOLD;
}