#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Konstanty
#define VSTUP "prenosy.dat"
#define VYSTUP "prenosy.html"
#define POCET_ZAZNAMU 14
#define VELIKOST_RADKU 200
#define ODDELOVAC " "

// Struktura, která uchovává čas
typedef struct {
    int hodiny;
    int minuty;
} CAS;

// Struktura, která uchovává datum
typedef struct {
    int den;
    int mesic;
    int rok;
} DATUM;

// Struktura uchovávající informace o přenosu
typedef struct {
    DATUM datum;
    CAS cas;
    char uzivatel[15];
    char ip[15];
    char soubor[15];
    int data;
} PRENOS;

// Načte datum z řetězce a následně ho vrátí
DATUM nactiDatum(const char *retezec) {
    DATUM datum;
    sscanf(retezec, "%d.%d.%d", &datum.den, &datum.mesic, &datum.rok);
    return datum;
}

// Načte čas z řetězce a následně ho vrátí
CAS nactiCas(const char *retezec) {
    CAS cas;
    sscanf(retezec, "%d:%d", &cas.hodiny, &cas.minuty);
    return cas;
}

// Načte číslo z řetězce obklopujícího "[" a "]"
int nactiVelikost(const char *retezec) {
    int velikost;
    sscanf(retezec, "[%d]", &velikost);
    return velikost;
}

// Načte vstupní data ze souobru "prenosy.dat" do pole struktur
int nactiData(PRENOS *prenosy) {
    FILE *fr = fopen(VSTUP, "r");
    char radek[VELIKOST_RADKU];
    char *udaj;
    int pocet;
    int i = 0;

    if (fr == NULL) {
        printf("Chyba pri otevirani souboru %s.\n", VSTUP);
        exit(EXIT_FAILURE);
    }

    while (fgets(radek, VELIKOST_RADKU, fr) != NULL) {
        pocet = 0;
        udaj = strtok(radek, ODDELOVAC);
        while (udaj != NULL) {
            switch (pocet) {
                case 0:
                    prenosy[i].datum = nactiDatum(udaj);
                    break;
                case 1:
                    prenosy[i].cas = nactiCas(udaj);
                    break;
                case 2:
                    // Načte nejprve uživatelské jméno až do "@" a pak IP
                    sscanf(udaj, "%[^@]@%s", prenosy[i].uzivatel, prenosy[i].ip);
                    break;
                case 3:
                    strcpy(prenosy[i].soubor, udaj);
                    break;
                case 4:
                    prenosy[i].data = nactiVelikost(udaj);
                    break;
                default:
                    break;
            }
            udaj = strtok(NULL, ODDELOVAC);
            pocet++;
        }
        i++;
    }

    if (fclose(fr) == EOF) {
        printf("Chyba pri uzavirani souboru %s.\n", VSTUP);
        exit(EXIT_FAILURE);
    }
    return i;
}

// Převede strukturu DATUM na řetězec, který vrátí v parametru
void datumNaRetezec(char *retezec, DATUM datum) {
    sprintf(retezec, "%d-%02d-%02d", datum.rok, datum.mesic, datum.den);
}

// Vypíše tabulku se záznamy do příkazové řádky
void vypisDoKonzole(const PRENOS *prenosy, int pocet) {
    DATUM datum;
    CAS cas;
    int prenesenaData = 0;
    PRENOS nejvetsi = prenosy[0];
    int pocetPreneseni = 0;

    printf("P R E N O S Y\n");
    printf("     datum   cas        uzivatel       ip adresa          soubor       data\n");
    printf("---------------------------------------------------------------------------\n");

    // Cyklus
    for (int i = 0; i < pocet; ++i) {
        datum = prenosy[i].datum;
        cas = prenosy[i].cas;
        prenesenaData += prenosy[i].data;

        if (prenosy[i].data > nejvetsi.data) {
            nejvetsi = prenosy[i];
        }

        printf(" %d.%d.%d %d:%02d    %12s   %13s    %12s   %8d\n", datum.den, datum.mesic, datum.rok, cas.hodiny,
               cas.minuty, prenosy[i].uzivatel, prenosy[i].ip, prenosy[i].soubor, prenosy[i].data);
    }

    // Spočítá, kolikrát byl soubor přenesen
    for (int i = 0; i < pocet; ++i) {
        if (strcmp(prenosy[i].soubor, nejvetsi.soubor) == 0) {
            pocetPreneseni++;
        }
    }

    // Statistiky
    printf("\nPocet zaznamu: %d\n", pocet);
    printf("Objem prenesenych dat: %d bytu\n", prenesenaData);
    printf("Nejvetsi soubor %s o velikosti %d bytu byl prenesen %d krat.\n", nejvetsi.soubor, nejvetsi.data,
           pocetPreneseni);

}

// Vytvoří do výstupního souboru HTML tabulku
void vypisDoSouboru(const PRENOS *prenosy, int pocet) {
    FILE *fw = fopen(VYSTUP, "w");
    char datum[11];
    int poradi = 0;

    if (fw == NULL) {
        printf("Chyba pri otevirani souboru %s.\n", VYSTUP);
        exit(EXIT_FAILURE);
    }

    fprintf(fw, "<style>\n");
    fprintf(fw, "td {border:1px dotted black;}\n");
    fprintf(fw, "</style>\n");

    fprintf(fw, "<h1>Prenosy</h1>\n");

    // Tabulka
    fprintf(fw, "<table>\n");

    // Hlavička
    fprintf(fw, "<tr>\n");

    fprintf(fw, "<th>poradi</th><th>user</th><th>ip</th><th>datum</th><th>cas</th><th>soubor</th><th>data</th>\n");

    fprintf(fw, "</tr>\n");

    // Data
    for (int i = 0; i < pocet; ++i) {
        if (prenosy[i].data > 500000 && strncmp(prenosy[i].ip, "10.", 3) == 0) {
            datumNaRetezec(datum, prenosy[i].datum);
            poradi++;

            fprintf(fw, "<tr>\n");
            fprintf(fw, "<td>%d</td><td>%s</td><td>%s</td><td>%s</td><td>%d:%02d</td><td>%s</td><td>%d</td>\n", poradi,
                    prenosy[i].uzivatel, prenosy[i].ip, datum, prenosy[i].cas.hodiny, prenosy[i].cas.minuty,
                    prenosy[i].soubor, prenosy[i].data);
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
    PRENOS prenosy[POCET_ZAZNAMU];
    int pocet;

    // Načtení vstupnich dat do pole
    pocet = nactiData(prenosy);

    // Kontrola, jestli se data načetla správně
    if (pocet != POCET_ZAZNAMU) {
        printf("Nekde se stala chyba pri nacitani dat ze souboru %s.\n", VSTUP);
        exit(EXIT_FAILURE);
    }

    // Výpisy
    vypisDoKonzole(prenosy, pocet);
    vypisDoSouboru(prenosy, pocet);
    return 0;
}
