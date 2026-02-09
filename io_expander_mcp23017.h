#ifndef IO_EXPANDER_MCP23017_H
#define IO_EXPANDER_MCP23017_H

#include "io_expander.h"
#include <Adafruit_MCP23017.h>

class MCP23017Expander : public IOExpander
{
public:
    MCP23017Expander() {}
    void begin() override { mcp.begin(); }
    uint8_t readPin(uint8_t pin) override { return mcp.digitalRead(pin); }
    void writePin(uint8_t pin, uint8_t value) override { mcp.digitalWrite(pin, value); }

private:
    Adafruit_MCP23017 mcp;
};

#endif // IO_EXPANDER_MCP23017_H