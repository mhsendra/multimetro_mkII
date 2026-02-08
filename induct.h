#ifndef MODE_INDUCTANCE_H
#define MODE_INDUCTANCE_H

float measureInd_raw();
float measureInd_calibrated();
void showInductance();
void showInductanceValue(float L);
void measureInductance();
void measureInd();              // ← ESTA ES LA QUE FALTABA
float measureInductancePulse();

#endif