#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Konstanty
#define POCET_OBCANU 14
#define DELKA_RADKU 200
#define ODDELOVAC " "

// Soubory
#define VSTUP "OBCANE.CSV"
#define VYSTUP "obcane.htm"

// Strutura uchovávající datum narození
typedef struct {
    int den;
    int mesic;
    int rok;
} NAROZENI;

// Struktura uchovávající data o občanovi
typedef struct {
    char jmeno[15];
    char prijmeni[20];
    char pohlavi[5];
    char rodneCislo[20];
    char mesto[15];
    NAROZENI datumNarozeni;
} OBCAN;

// Určí, jestli se jedná o muže nebo o ženu
int jeZena(const char *rodneCislo) {
    if (rodneCislo[2] == '5' || rodneCislo[2] == '6') {
        return 1;
    }
    return 0;
}

// Vypočítá z předaného rodného čísla datum narození
NAROZENI vypocitejNarozeni(const char *rodneCislo) {
    NAROZENI narozeni;
    char den[3];
    char mesic[3];
    char rok[3];

    // Získá rok
    strncpy(rok, rodneCislo, 2);
    rok[2] = '\0';
    narozeni.rok = 1900 + atoi(rok);

    // Získá měsíc
    strncpy(mesic, rodneCislo + 2, 2);
    mesic[2] = '\0';
    narozeni.mesic = jeZena(rodneCislo) ? atoi(mesic) - 50 : atoi(mesic);

    // Získá den
    strncpy(den, rodneCislo + 4, 2);
    den[2] = '\0';
    narozeni.den = atoi(den);

    return narozeni;
}

// Načte data z .csv souboru do pole
int nactiData(OBCAN *obcane) {
    FILE *fr = fopen(VSTUP, "r");
    char radek[DELKA_RADKU];
    char *udaj;
    int i;
    int pocet = 0;

    if (fr == NULL) {
        printf("Chyba pri otevirani souboru %s.\n", VSTUP);
        exit(EXIT_FAILURE);
    }

    while (fgets(radek, DELKA_RADKU, fr) != NULL) {
        udaj = strtok(radek, ODDELOVAC);
        i = 0;
        while (udaj != NULL) {
            switch (i) {
                case 0:
                    strcpy(obcane[pocet].jmeno, udaj);
                    break;
                case 1:
                    strcpy(obcane[pocet].prijmeni, udaj);
                    break;
                case 2:
                    strcpy(obcane[pocet].rodneCislo, udaj);
                    break;
                case 3:
                    strcpy(obcane[pocet].mesto, udaj);
                    break;
                default:
                    break;
            }
            udaj = strtok(NULL, ODDELOVAC);
            i++;
        }
        // Určení pohlaví na základě rodného čísla
        strcpy(obcane[pocet].pohlavi, jeZena(obcane[pocet].rodneCislo) ? "zena" : "muz");

        // Načtení data narození z rodného čísla
        obcane[pocet].datumNarozeni = vypocitejNarozeni(obcane[pocet].rodneCislo);
        pocet++;
    }

    if (fclose(fr) == EOF) {
        printf("Chyba pri uzavirani souboru %s.\n", VSTUP);
        exit(EXIT_FAILURE);
    }

    return pocet;
}

// Zapíše data do souboru jako HTML tabulky
void zapisDoSouboru(const OBCAN *obcane, int pocet) {
    FILE *fw = fopen(VYSTUP, "w");

    if (fw == NULL) {
        printf("Chyba pri otevirani souboru %s.\n", VYSTUP);
        exit(EXIT_FAILURE);
    }

    // Výpis žen
    fprintf(fw, "<h1>Zeny</h1>\n");
    fprintf(fw, "<table>\n");
    for (int i = 0; i < pocet; ++i) {
        if (strcmp(obcane[i].pohlavi, "zena") == 0) {
            fprintf(fw, "<tr>\n");
            fprintf(fw, "<td>%s</td><td>%s</td><td>%d. %d. %d</td><td>%s</td>\n", obcane[i].jmeno, obcane[i].prijmeni,
                    obcane[i].datumNarozeni.den, obcane[i].datumNarozeni.mesic, obcane[i].datumNarozeni.rok,
                    obcane[i].mesto);
            fprintf(fw, "</tr>\n");
        }
    }
    fprintf(fw, "</table>\n");

    // Výpis mužů
    fprintf(fw, "<h1>Muzi</h1>\n");
    fprintf(fw, "<table>\n");
    for (int i = 0; i < pocet; ++i) {
        if (strcmp(obcane[i].pohlavi, "muz") == 0) {
            fprintf(fw, "<tr>\n");
            fprintf(fw, "<td>%s</td><td>%s</td><td>%d. %d. %d</td><td>%s</td>\n", obcane[i].jmeno, obcane[i].prijmeni,
                    obcane[i].datumNarozeni.den, obcane[i].datumNarozeni.mesic, obcane[i].datumNarozeni.rok,
                    obcane[i].mesto);
            fprintf(fw, "</tr>\n");
        }
    }
    fprintf(fw, "</table>\n");

    if (fclose(fw) == EOF) {
        printf("Chyba pri uzavirani souboru %s.\n", VYSTUP);
        exit(EXIT_FAILURE);
    }
}

int main() {
    OBCAN obcane[POCET_OBCANU];
    int pocet;

    // Načtení dat do pole struktur OBCAN
    pocet = nactiData(obcane);

    // Kontrola, jestli se načetla všechna data
    if (pocet != POCET_OBCANU) {
        printf("Chyba pri nacitani dat ze souboru %s.\n", VSTUP);
        exit(EXIT_FAILURE);
    }

    // Zapíše tabulku do HTML souboru
    zapisDoSouboru(obcane, pocet);
    return 0;
}
