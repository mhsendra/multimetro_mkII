#ifndef IO_EXPANDER_PCF8574_H
#define IO_EXPANDER_PCF8574_H

#include <PCF8574.h>
#include "io_expander.h"

class PCF8574Expander : public IOExpander
{
public:
    PCF8574Expander(uint8_t addr)
        : pcf(addr), state(0xFF) {} // todo HIGH al arrancar

    void begin() override
    {
        pcf.begin();
        pcf.write8(state); // inicializa puerto completo
    }

    void pinMode(uint8_t pin, uint8_t mode) override
    {
        if (mode == INPUT)
            state |= (1 << pin); // HIGH → entrada
        else
            state &= ~(1 << pin); // LOW → salida

        pcf.write8(state);
    }

    void digitalWrite(uint8_t pin, uint8_t value) override
    {
        if (value == HIGH)
            state |= (1 << pin);
        else
            state &= ~(1 << pin);

        pcf.write8(state);
    }

    int digitalRead(uint8_t pin) override
    {
        return pcf.read(pin);
    }

private:
    PCF8574 pcf;
    uint8_t state;
};

#endif