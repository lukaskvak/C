// funkcie.h
#ifndef FUNKCIE_H
#define FUNKCIE_H

#include "hokejovy_turnaj.h"

void nacitajTimyZoSuboru(HokejovyTurnaj* turnaj, const char* nazovSuboru);
void simulujTurnaj(HokejovyTurnaj* turnaj);
void zobrazVysledkyTurnaja(HokejovyTurnaj* turnaj);

#endif // FUNKCIE_H
