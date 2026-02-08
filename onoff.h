#ifndef ONOFF_H
#define ONOFF_H

#include <Arduino.h>
#include "pins.h"

class OnOff {
public:
    void begin();
    bool isOn();
};

#endif