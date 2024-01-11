// funkcie.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funkcie.h"

void nacitajTimyZoSuboru(HokejovyTurnaj* turnaj, const char* nazovSuboru) {
    FILE* subor = fopen(nazovSuboru, "r");
    if (subor == NULL) {
        printf("Chyba pri otvarani suboru %s\n", nazovSuboru);
        exit(EXIT_FAILURE);
    }

    // Zisti pocet riadkov v subore
    int pocetTimov = 0;
    char riadok[50];
    while (fgets(riadok, sizeof(riadok), subor) != NULL) {
        pocetTimov++;
    }

    // Vrat sa na zaciatok suboru
    rewind(subor);

    turnaj->timy = (Tim*)malloc(pocetTimov * sizeof(Tim));
    turnaj->pocetTimov = pocetTimov;

    // Nacitaj timy zo suboru
    for (int i = 0; i < pocetTimov; i++) {
        fgets(turnaj->timy[i].nazov, sizeof(turnaj->timy[i].nazov), subor);
        // Odstrani newline znak zo vstupu
        strtok(turnaj->timy[i].nazov, "\n");
        turnaj->timy[i].golyZa = 0;
        turnaj->timy[i].golyProti = 0;
        turnaj->timy[i].body = 0;
    }

    fclose(subor);
}

void simulujTurnaj(HokejovyTurnaj* turnaj) {
    srand(time(NULL));

    for (int i = 0; i < turnaj->pocetTimov; i++) {
        for (int j = i + 1; j < turnaj->pocetTimov; j++) {
            int golyTim1 = rand() % 11;
            int golyTim2 = rand() % 11;

            turnaj->timy[i].golyZa += golyTim1;
            turnaj->timy[i].golyProti += golyTim2;
            turnaj->timy[j].golyZa += golyTim2;
            turnaj->timy[j].golyProti += golyTim1;

            if (golyTim1 > golyTim2) {
                turnaj->timy[i].body += 2; // Vyhra
            } else if (golyTim1 == golyTim2) {
                turnaj->timy[i].body += 1; // Remiza
                turnaj->timy[j].body += 1;
            } else {
                turnaj->timy[j].body += 2; // Vyhra
            }

            printf("%s (%d) - %s (%d)\n", turnaj->timy[i].nazov, golyTim1, turnaj->timy[j].nazov, golyTim2);
        }
    }
}

void zobrazVysledkyTurnaja(HokejovyTurnaj* turnaj) {
    // Zorad timy podla poctu bodov a rozdielu golov
    for (int i = 0; i < turnaj->pocetTimov - 1; i++) {
        for (int j = i + 1; j < turnaj->pocetTimov; j++) {
            if (turnaj->timy[i].body < turnaj->timy[j].body ||
                (turnaj->timy[i].body == turnaj->timy[j].body && turnaj->timy[i].golyZa < turnaj->timy[j].golyZa)) {
                // Vymena pozicii
                Tim temp = turnaj->timy[i];
                turnaj->timy[i] = turnaj->timy[j];
                turnaj->timy[j] = temp;
            }
        }
    }

    // Zobraz vysledky
    printf("Poradie. Nazov timu Pocet strelenych golov: Pocet vstrelenych golov Pocet bodov\n");
    for (int i = 0; i < turnaj->pocetTimov; i++) {
        printf("%d. %s %d:%d %d\n", i + 1, turnaj->timy[i].nazov, turnaj->timy[i].golyZa, turnaj->timy[i].golyProti, turnaj->timy[i].body);
    }
}
