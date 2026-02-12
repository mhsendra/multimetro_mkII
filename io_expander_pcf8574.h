#ifndef IO_EXPANDER_PCF8574_H
#define IO_EXPANDER_PCF8574_H

#include <PCF8574.h>
#include "io_expander.h"

class PCF8574Expander : public IOExpander
{
public:
    PCF8574Expander(uint8_t address) : expander(address) {}

    void begin() { expander.begin(); }

    void pinMode(uint8_t pin, uint8_t mode) override
    {
        if (mode == OUTPUT)
            expander.write(pin, LOW);
    }

    void digitalWrite(uint8_t pin, uint8_t value) override
    {
        expander.write(pin, value);
    }

    int digitalRead(uint8_t pin) override
    {
        return expander.read(pin);
    }

private:
    PCF8574 expander;
};

#endif