#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Konstanty
#define VSTUP "cyklistika.txt"
#define VYSTUP "vysledkova_listina.txt"
#define POCET_CYKLISTU 108
#define DELKA_RADKU 200
#define ODDELOVAC ";"

// Struktura uchovávající čas
typedef struct {
    int hodiny;
    int minuty;
    int sekundy;
    int desetiny;
} CAS;

// Struktura s informacemi o cyklistovi
typedef struct {
    int cislo;
    char prijmeni[20];
    char jmeno[15];
    char narodnost[4];
    int rocnik;
    char klub[40];
    CAS cas;
} CYKLISTA;

// Načte čas z řetězce a vrátí strukturu CAS
CAS nactiCas(const char *retezec) {
    CAS cas;
    sscanf(retezec, "%d:%d:%d.%d", &cas.hodiny, &cas.minuty, &cas.sekundy, &cas.desetiny);
    return cas;
}

// Vrátí věk cyklisty
int vekCyklisty(CYKLISTA cyklista) {
    time_t sekundy = time(NULL);
    struct tm *aktualniCas = localtime(&sekundy);

    return (aktualniCas->tm_year + 1900) - cyklista.rocnik;
}

// Vrátí čas v desetinách
int casNaDesetiny(CAS cas) {
    return (cas.hodiny * 36000) + (cas.minuty * 600) + (cas.sekundy * 10) + cas.desetiny;
}

// Vymění parametry cyklistů
void vymen(CYKLISTA *c1, CYKLISTA *c2) {
    CYKLISTA c3 = *c1;
    *c1 = *c2;
    *c2 = c3;
}

// Seřadí cyklisty podle celkového času vzestupně (bubble sort)
void serad(CYKLISTA *cyklisti, int pocet) {
    int i, j;
    int vymena;
    for (i = 0; i < pocet - 1; i++) {
        vymena = 0;
        for (j = 0; j < pocet - i - 1; j++) {
            if (casNaDesetiny(cyklisti[j].cas) > casNaDesetiny(cyklisti[j + 1].cas)) {
                vymen(&cyklisti[j], &cyklisti[j + 1]);
                vymena = 1;
            }
        }
        if (vymena == 0)
            break;
    }
}

// Z počtu desetin předaných v parametru vypočítá a vrátí strukturu CAS
CAS desetinyNaCas(int desetiny) {
    CAS cas;
    cas.hodiny = desetiny / 36000;
    cas.minuty = (desetiny % 36000) / 600;
    cas.sekundy = (desetiny % 600) / 10;
    cas.desetiny = desetiny % 10;
    return cas;
}

// Převede strukturu času na řetězec na základě formátu
void casNaRetezec(char *retezec, CAS cas, const char *format) {
    sprintf(retezec, format, cas.hodiny, cas.minuty, cas.sekundy, cas.desetiny);
}

// Načte data ze vstupního souboru "cyklistika.txt"
int nactiData(CYKLISTA *cyklisti) {
    FILE *fr = fopen(VSTUP, "r");
    char radek[DELKA_RADKU];
    char *udaj;
    int pocet;
    int i = 0;

    if (fr == NULL) {
        printf("Chyba pri otevirani souboru %s.\n", VSTUP);
        exit(EXIT_FAILURE);
    }

    // Načtení všech dat
    while (fgets(radek, DELKA_RADKU, fr) != NULL) {
        if (i > 0) {
            udaj = strtok(radek, ODDELOVAC);
            pocet = 0;

            while (udaj != NULL) {
                switch (pocet) {
                    case 0:
                        cyklisti[i - 1].cislo = atoi(udaj);
                        break;
                    case 1:
                        strcpy(cyklisti[i - 1].prijmeni, udaj);
                        break;
                    case 2:
                        strcpy(cyklisti[i - 1].jmeno, udaj);
                        break;
                    case 3:
                        strcpy(cyklisti[i - 1].narodnost, udaj);
                        break;
                    case 4:
                        cyklisti[i - 1].rocnik = atoi(udaj);
                        break;
                    case 5:
                        strcpy(cyklisti[i - 1].klub, udaj);
                        break;
                    case 6:
                        cyklisti[i - 1].cas = nactiCas(udaj);
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
        printf("Chyba pri uzavirani souboru %s.\n", VYSTUP);
        exit(EXIT_FAILURE);
    }
    return i - 1;
}

// Vypíše tabulku na obrazovku
void vypisNaObrazovku(const CYKLISTA *cyklisti, int pocet) {
    CYKLISTA c;
    CAS cas;
    CYKLISTA nejstarsi = cyklisti[0];
    int pocetCechu = 0;
    int pocetSlovaku = 0;

    printf("S T A R T O V N I  L I S T I N A  -  O B R  D R A S A L\n");
    printf("------------------------------------------------------------------------------------------------------\n");
    printf("startovni cislo|   prijmeni  |  jmeno   |narodnost|rocnik|              klub              |   cas    |\n");
    printf("------------------------------------------------------------------------------------------------------\n");

    // Výpis dat
    for (int i = 0; i < pocet; ++i) {
        c = cyklisti[i];
        cas = c.cas;

        // Zjištění nejstaršího cyklisty
        if (c.rocnik < nejstarsi.rocnik) {
            nejstarsi = c;
        }

        // Celkem čechů
        if (strcmp(c.narodnost, "CZE") == 0) {
            pocetCechu++;
        }

        // Celkem slováků
        if (strcmp(c.narodnost, "SVK") == 0) {
            pocetSlovaku++;
        }

        printf("           %d|%13s|%10s|      %3s|  %d|%32s|%2d:%02d:%02d.%d|\n", c.cislo, c.prijmeni, c.jmeno,
               c.narodnost, c.rocnik,
               c.klub, cas.hodiny, cas.minuty, cas.sekundy, cas.desetiny);
    }
    printf("------------------------------------------------------------------------------------------------------\n");
    printf("Na startu je %d zavodniku.\n", pocet);
    printf("Nejstarsim zavodnikem je %s %s narozen v roce %d. Je mu %d let.\n", nejstarsi.jmeno, nejstarsi.prijmeni,
           nejstarsi.rocnik, vekCyklisty(nejstarsi));
    printf("Zavodnici dle narodnosti: Cesi    - %d\n", pocetCechu);
    printf("                          Slovaci - %d\n", pocetSlovaku);
    printf("                          Jine    - %d\n", pocet - pocetCechu - pocetSlovaku);
}

// Zapíše tabulku do souboru "vysledkova_listina.txt"
void zapisDoSouboru(const CYKLISTA *cyklisti, int pocet) {
    FILE *fw = fopen(VYSTUP, "w");
    CYKLISTA c;
    CAS ztrata;
    char casText[15];
    char ztrataText[15];

    if (fw == NULL) {
        printf("Chyba pri otevirani souboru %s.\n", VYSTUP);
        exit(EXIT_FAILURE);
    }

    printf("\nByl vytvoren soubor %s.\n", VYSTUP);

    fprintf(fw, "V Y S L E D K O V A  L I S T I N A  -  O B R  D R A S A L\n");
    fprintf(fw,
            "-------------------------------------------------------------------------------------------------------------------------\n");
    fprintf(fw,
            "poradi|startovni cislo|   prijmeni  |  jmeno   |narodnost|rocnik|              klub              |   cas    |   ztrata  |\n");
    fprintf(fw,
            "-------------------------------------------------------------------------------------------------------------------------\n");

    // Výpis cyklistů
    for (int i = 0; i < pocet; ++i) {
        c = cyklisti[i];
        ztrata = desetinyNaCas(casNaDesetiny(c.cas) - casNaDesetiny(cyklisti[0].cas));
        casNaRetezec(casText, c.cas, "%2d:%02d:%02d.%d");
        casNaRetezec(ztrataText, ztrata, "%02d:%02d:%02d.%d");

        fprintf(fw, "   %3d|           %d|%13s|%10s|      %3s|  %4d|%32s|%s|%s%s|\n", i + 1, c.cislo, c.prijmeni, c.jmeno, c.narodnost, c.rocnik,
                c.klub, casText, i == 0 ? "" : "+", i == 0 ? "           " : ztrataText);
    }

    if (fclose(fw) == EOF) {
        printf("Chyba pri uzavirani souboru %s.\n", VYSTUP);
        exit(EXIT_FAILURE);
    }
}

int main() {
    CYKLISTA cyklisti[POCET_CYKLISTU];
    int pocet;

    // Načtení a testování dat
    pocet = nactiData(cyklisti);
    if (pocet != POCET_CYKLISTU) {
        printf("Nekde se stala chyba pri nacitani dat ze souboru %s.\n", VSTUP);
        exit(EXIT_FAILURE);
    }

    // Výpis na obrazovku
    vypisNaObrazovku(cyklisti, pocet);

    // Setřídění cyklistů podle času vzestupně
    serad(cyklisti, pocet);

    // Zápis do výstupního souboru
    zapisDoSouboru(cyklisti, pocet);
    return 0;
}
