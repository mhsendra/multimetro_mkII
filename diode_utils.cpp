#include "diode_utils.h"
#include "adc.h"
#include "pins.h"
#include "config.h"

// Devuelve true si hay conducción entre pinA → pinB
bool diodeConducts(uint8_t pinA, uint8_t pinB) {

    // 1) Configurar pinA como salida y ponerlo a HIGH
    pinMode(pinA, OUTPUT);
    digitalWrite(pinA, HIGH);

    // 2) Configurar pinB como entrada analógica
    pinMode(pinB, INPUT);

    delayMicroseconds(200);

    // 3) Leer tensión en pinB
    float v = readADC_Pin(pinB);   // <-- si no tienes readADC_Pin, te lo genero

    // 4) Resetear pines
    pinMode(pinA, INPUT);
    pinMode(pinB, INPUT);

    // 5) Conducción si la caída es > 0.15V
    return (v > 0.15f);
}