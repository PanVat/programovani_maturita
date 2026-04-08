#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Konstanty
#define VSTUP "zavodnici.txt"
#define VYSTUP "vysledkova_listina.txt"
#define POCET_ZAVODNIC 12
#define VELIKOST_RADKU 200
#define ODDELOVAC " "

// Struktura času
typedef struct {
    int minuty;
    int sekundy;
    int setiny;
} CAS;

// Struktura závodnic
typedef struct {
    int cislo;
    char prijmeni[20];
    char jmeno[15];
    CAS kolo1;
    CAS kolo2;
} ZAVODNICE;

// Převede textový řetězec na strukturu času
CAS casZRetezce(const char *retezec) {
    CAS cas;
    sscanf(retezec, "%d:%d.%d", &cas.minuty, &cas.sekundy, &cas.setiny);
    return cas;
}

// Vypíše čas v předaném formátu do konzole nebo souboru
void vypisCas(CAS cas, const char *format, FILE *mod) {
    fprintf(mod, format, cas.minuty, cas.sekundy, cas.setiny);
}

// Převede strukturu času na setiny a následně ji vrátí
int casNaSetiny(CAS cas) {
    return cas.setiny + (cas.sekundy * 100) + (cas.minuty * 6000);
}

// Převede setiny předané v parametru na časovou strukturu, kterou vrátí
CAS setinyNaCas(int setiny) {
    CAS cas;
    cas.setiny = setiny % 100;

    int celkemSekund = setiny / 100;
    cas.sekundy = celkemSekund % 60;

    cas.minuty = celkemSekund / 60;

    return cas;
}

// Vypočítá součet dvou struktur časů a výslednou strukturu vrátí
CAS soucetCasu(CAS cas1, CAS cas2) {
    CAS celkovyCas;
    celkovyCas = setinyNaCas(casNaSetiny(cas1) + casNaSetiny(cas2));
    return celkovyCas;
}

// Prohodí parametry
void vymen(ZAVODNICE *zav1, ZAVODNICE *zav2) {
    ZAVODNICE doc = *zav1;
    *zav1 = *zav2;
    *zav2 = doc;
}

// Bubble sort, který seřadí pole závodnic od nejrychlejší
void serad(ZAVODNICE *zavodnice, int pocet) {
    int vymeneno;
    for (int i = 0; i < pocet - 1; ++i) {
        vymeneno = 0;
        for (int j = 0; j < pocet - i - 1; ++j) {
            if (casNaSetiny(soucetCasu(zavodnice[j].kolo1, zavodnice[j].kolo2)) >
                casNaSetiny(soucetCasu(zavodnice[j + 1].kolo1, zavodnice[j + 1].kolo2))) {
                vymen(&zavodnice[j], &zavodnice[j + 1]);
                vymeneno = 1;
            }
        }
        if (vymeneno == 0) {
            break;
        }
    }
}

// Načte data o závodnicích ze souboru "zavodnici.txt"
int nactiData(ZAVODNICE *zavodnice) {
    FILE *fr = fopen(VSTUP, "r");
    char radek[VELIKOST_RADKU];
    char *udaj;
    int pocet;
    int i = 0;

    if (fr == NULL) {
        printf("Chyba pri nacitani souboru %s.\n", VSTUP);
        return -1;
    }
    while (fgets(radek, VELIKOST_RADKU, fr) != NULL) {
        if (i > 0) {
            pocet = 0;
            udaj = strtok(radek, ODDELOVAC);
            while (udaj != NULL) {
                switch (pocet) {
                    case 0:
                        zavodnice[i - 1].cislo = atoi(udaj);
                        break;
                    case 1:
                        strcpy(zavodnice[i - 1].prijmeni, udaj);
                        break;
                    case 2:
                        strcpy(zavodnice[i - 1].jmeno, udaj);
                        break;
                    case 3:
                        zavodnice[i - 1].kolo1 = casZRetezce(udaj);
                        break;
                    case 4:
                        zavodnice[i - 1].kolo2 = casZRetezce(udaj);
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
        return -1;
    }
    return i - 1;
}

// Vypíše tabulku do příkazové řádky
void vypisDoKonzole(const ZAVODNICE *zavodnice, int pocet) {
    printf("S T A R T O V N I  L I S T I N A  -  S L A L O M  Z E N Y\n");
    printf("---------------------------------------------------------\n");
    printf("startovni cislo|  prijmeni  |  jmeno |cas 1. kola|cas 2. kola\n");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < pocet; ++i) {
        printf("%15d|%12s|%8s|    ", zavodnice[i].cislo, zavodnice[i].prijmeni,
               zavodnice[i].jmeno);
        vypisCas(zavodnice[i].kolo1, "%d:%02d.%02d", stdout);
        printf("|    ");
        vypisCas(zavodnice[i].kolo2, "%d:%02d.%02d", stdout);
        printf("\n");
    }
    printf("-------------------------------------------------------------\n");
}

// Zapíše tabulku do souboru
void zapisDoSouboru(ZAVODNICE *zavodnice, int pocet) {
    FILE *fw = fopen(VYSTUP, "w");
    CAS casSoucet;
    CAS ztrata;
    int rozdilCasu;

    serad(zavodnice, pocet);

    int casVitezeSetiny = casNaSetiny(soucetCasu(zavodnice[0].kolo1, zavodnice[0].kolo2));

    if (fw == NULL) {
        printf("Chyba pri nacitani souboru %s.\n", VYSTUP);
        exit(EXIT_FAILURE);
    }

    printf("Byl vytvoren soubor %s.\n", VYSTUP);

    fprintf(fw, "V Y S L E D K O V A  L I S T I N A\n");
    fprintf(fw, "----------------------------------\n");
    fprintf(fw, "poradi|cislo|  prijmeni  |  jmeno | 1.kolo| 2.kolo| celkem |   ztrata\n");
    fprintf(fw, "---------------------------------------------------------------------\n");

    for (int i = 0; i < pocet; ++i) {
        casSoucet = soucetCasu(zavodnice[i].kolo1, zavodnice[i].kolo2);

        rozdilCasu = casNaSetiny(casSoucet) - casVitezeSetiny;
        ztrata = setinyNaCas(rozdilCasu);

        fprintf(fw, "%6d|  %3d|%12s|%8s|", i + 1, zavodnice[i].cislo, zavodnice[i].prijmeni, zavodnice[i].jmeno);
        vypisCas(zavodnice[i].kolo1, "%d:%02d.%02d", fw);
        fprintf(fw, "|");
        vypisCas(zavodnice[i].kolo2, "%d:%02d.%02d", fw);
        fprintf(fw, "|");
        vypisCas(casSoucet, "%02d:%02d.%02d", fw);
        if (i == 0) {
            fprintf(fw, "|\n");
        } else {
            fprintf(fw, "|+");
            vypisCas(ztrata, "%02d:%02d.%02d", fw);
            fprintf(fw, "\n");
        }
    }

    if (fclose(fw) == EOF) {
        printf("Chyba pri uzavirani souboru %s.\n", VYSTUP);
        exit(EXIT_FAILURE);
    }
}

int main() {
    ZAVODNICE zavodnice[POCET_ZAVODNIC];
    int pocet;

    // Test, jestli se správně načetly všechny závodnice
    pocet = nactiData(zavodnice);
    if (pocet != POCET_ZAVODNIC) {
        printf("Chyba pri nacitani dat ze souboru %s.\n", VSTUP);
        return -1;
    }

    // Výpisy
    vypisDoKonzole(zavodnice, pocet);
    zapisDoSouboru(zavodnice, pocet);

    return 0;
}