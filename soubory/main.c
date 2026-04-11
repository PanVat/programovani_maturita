#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Konstanty
#define VSTUP "soubory.txt"
#define VYSTUP "vypis_souboru.htm"
#define POCET_SOUBORU 8
#define DELKA_RADKU 200
#define ODDELOVAC " "

// Struktura obsahující informace o souborech
typedef struct {
    char nazev[15];
    char pripona[4];
    char datum[9];
    char atribut[2];
    int velikost;
} SOUBOR;

// Struktura obsahující datum
typedef struct {
    int den;
    int mesic;
    int rok;
} DATUM;

// Převede datum ve formátu RRRRmmdd do české podoby
DATUM prevedDatum(const char *retezec) {
    DATUM datum;
    sscanf(retezec, "%4d%2d%2d", &datum.rok, &datum.mesic, &datum.den);
    return datum;
}

// Načte data ze vstupního souboru do pole struktur SOUBOR
int nactiData(SOUBOR *soubory) {
    FILE *fr = fopen(VSTUP, "r");
    char radek[DELKA_RADKU];
    char *udaj;
    int i = 0;
    int pocet;

    if (fr == NULL) {
        printf("Chyba pri otevirani souboru %s.\n", VSTUP);
        exit(EXIT_FAILURE);
    }

    // Načtení dat
    while (fgets(radek, DELKA_RADKU, fr) != NULL) {
        if (i > 0) {
            udaj = strtok(radek, ODDELOVAC);
            pocet = 0;
            while (udaj != NULL) {
                switch (pocet) {
                    case 0:
                        strcpy(soubory[i - 1].nazev, udaj);
                        break;
                    case 1:
                        strcpy(soubory[i - 1].pripona, udaj);
                        break;
                    case 2:
                        strcpy(soubory[i - 1].datum, udaj);
                        break;
                    case 3:
                        strcpy(soubory[i - 1].atribut, udaj);
                        break;
                    case 4:
                        soubory[i - 1].velikost = atoi(udaj);
                        break;
                    default:
                        break;
                }
                udaj = strtok(NULL, ODDELOVAC);
                pocet++;
            }
        }
        i++;
    }

    if (fclose(fr) == EOF) {
        printf("Chyba pri uzavirani souboru %s.\n", VSTUP);
        exit(EXIT_FAILURE);
    }
    return i - 1;
}

// Vypíše statistiky o záznamech do konzole
void vypisStatistiky(const SOUBOR *soubory, int pocet) {
    SOUBOR nejmensi = soubory[0];
    int skryteSoubory = 0;
    int systemoveSoubory = 0;

    // Projede všechny soubory
    for (int i = 0; i < pocet; i++) {
        if (strcmp(soubory[i].atribut, "H") == 0) {
            skryteSoubory++;
        }
        if (strcmp(soubory[i].atribut, "S") == 0) {
            systemoveSoubory++;
        }
        if (soubory[i].velikost < nejmensi.velikost) {
            nejmensi = soubory[i];
        }
    }

    // Výpis statistik
    printf("Pocet zaznamu v souboru je %d.\n", pocet);
    printf("Pocet skrytych souboru je %d.\n", skryteSoubory);
    printf("Pocet systemovych souboru je %d.\n", systemoveSoubory);
    printf("Soubor s nejmensi velikosti %d je %s.%s.\n", nejmensi.velikost, nejmensi.nazev, nejmensi.pripona);
}

// Vytvoří soubor obsahující HTML tabulku s údaji o souborech
void vytvorTabulku(const SOUBOR *soubory, int pocet) {
    DATUM datum;

    FILE *fw = fopen(VYSTUP, "w");

    if (fw == NULL) {
        printf("Chyba pri otevirani souboru %s.\n", VYSTUP);
        exit(EXIT_FAILURE);
    }

    fprintf(fw, "<h1>Seznam souboru</h1>\n");

    // Tabulka
    fprintf(fw, "<table>\n");

    fprintf(fw, "<tr>\n");
    fprintf(fw, "<th>jmeno</th><th>velikost</th><th>datum</th><th>atribut</th>\n");
    fprintf(fw, "</tr>\n");

    for (int i = 0; i < pocet; i++) {
        datum = prevedDatum(soubory[i].datum);
        fprintf(fw, "<tr>\n");
        fprintf(fw, "<td>%s.%s</td><td>%d</td><td>%d.%d.%d</td><td>%s</td>\n", soubory[i].nazev, soubory[i].pripona,
                soubory[i].velikost, datum.den, datum.mesic, datum.rok, soubory[i].atribut);
        fprintf(fw, "</tr>\n");
    }

    fprintf(fw, "</table>\n");

    if (fclose(fw) == EOF) {
        printf("Chyba pri uzavirani souboru %s.\n", VYSTUP);
        exit(EXIT_FAILURE);
    }
}

int main(void) {
    // Pole struktur SOUBOR
    SOUBOR soubory[POCET_SOUBORU];
    int pocet;

    // Načte a otestuje data
    pocet = nactiData(soubory);
    if (pocet != POCET_SOUBORU) {
        printf("Nekde se stala chyba pri nacitani dat ze souboru %s.\n", VSTUP);
        exit(EXIT_FAILURE);
    }

    // Výpisy dat
    vypisStatistiky(soubory, pocet);
    vytvorTabulku(soubory, pocet);

    return 0;
}
