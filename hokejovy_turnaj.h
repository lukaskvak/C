// hokejovy_turnaj.h
#ifndef HOKEJOVY_TURNAJ_H
#define HOKEJOVY_TURNAJ_H

typedef struct {
    char nazov[50];
    int golyZa;
    int golyProti;
    int body;
} Tim;

typedef struct {
    Tim* timy;
    int pocetTimov;
} HokejovyTurnaj;

void nacitajTimyZoSuboru(HokejovyTurnaj* turnaj, const char* nazovSuboru);
void simulujTurnaj(HokejovyTurnaj* turnaj);
void zobrazVysledkyTurnaja(HokejovyTurnaj* turnaj);

#endif // HOKEJOVY_TURNAJ_H
