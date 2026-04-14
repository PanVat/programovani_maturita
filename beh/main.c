#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Konstanty
#define VSTUP "beh.txt"
#define VYSTUP "vysledkova_listina.txt"
#define DELKA_RADKU 200
#define POCET_BEZCU 22
#define ODDELOVAC ";"

// Struktura obsahující údaje o datu
typedef struct {
    int den;
    int mesic;
    int rok;
} DATUM;

// Struktura obsahující údaje o času
typedef struct {
    int hodiny;
    int minuty;
    int sekundy;
} CAS;

// Struktura obsahující údaje o běžci
typedef struct {
    int cislo;
    char prijmeni[20];
    char jmeno[15];
    DATUM narozeni;
    char stat[4];
    char oddil[40];
    CAS cas;
} BEZEC;

// Z řetězce vyparsuje datum a vrátí ho jako strukturu
DATUM nactiDatum(const char *retezec) {
    DATUM datum;
    sscanf(retezec, "%d.%d.%d", &datum.den, &datum.mesic, &datum.rok);
    return datum;
}

// Z řetězce vyparsuje čas a vrátí ho jako strukturu
CAS nactiCas(const char *retezec) {
    CAS cas;
    sscanf(retezec, "%d:%d:%d", &cas.hodiny, &cas.minuty, &cas.sekundy);
    return cas;
}

// Ze struktury CAS vytvoří řetězec a vrátí ho v parametru
void casNaRetezec(char *retezec, CAS cas, const char *format) {
    sprintf(retezec, format, cas.hodiny, cas.minuty, cas.sekundy);
}

// Funkce vrací, jestli je starší první (1) nebo druhé datum (0)
int jeStarsi(DATUM d1, DATUM d2) {
    if (d1.rok != d2.rok) {
        return d1.rok < d2.rok;
    }
    if (d1.mesic != d2.mesic) {
        return d1.mesic < d2.mesic;
    }
    return d1.den < d2.den;
}

// Vrátí věk běžce
int vekBezce(BEZEC bezec) {
    time_t ted = time(NULL);
    struct tm *aktualniCas = localtime(&ted);

    return (aktualniCas->tm_year + 1900) - bezec.narozeni.rok;
}

// Převede strukturu času na sekundy
int casNaSekudy(CAS cas) {
    return (cas.hodiny * 3600) + (cas.minuty * 60) + cas.sekundy;
}

// Převede sekundy na strukturu času
CAS sekundyNaCas(int sekundy){
    CAS cas;
    cas.hodiny = sekundy / 3600;
    cas.minuty = (sekundy % 3600) / 60;
    cas.sekundy = sekundy % 60;
    return cas;
}

// Vymění hodnoty parametrů typu BEZEC
void vymen(BEZEC *b1, BEZEC *b2) {
    BEZEC b3 = *b1;
    *b1 = *b2;
    *b2 = b3;
}

// Seřadí pole dle dosaženého času vzestupně (bubble sort)
void serad(BEZEC *bezci, int pocet) {
    int i, j;
    int vymena;
    for (i = 0; i < pocet - 1; i++) {
        vymena = 0;
        for (j = 0; j < pocet - i - 1; j++) {
            if (casNaSekudy(bezci[j].cas) > casNaSekudy(bezci[j + 1].cas)) {
                vymen(&bezci[j], &bezci[j + 1]);
                vymena = 1;
            }
        }
        if (vymena == 0)
            break;
    }
}

// Načte data do pole struktur BEZEC
int nactiData(BEZEC *bezci) {
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
                        bezci[i - 1].cislo = atoi(udaj);
                        break;
                    case 1:
                        strcpy(bezci[i - 1].prijmeni, udaj);
                        break;
                    case 2:
                        strcpy(bezci[i - 1].jmeno, udaj);
                        break;
                    case 3:
                        bezci[i - 1].narozeni = nactiDatum(udaj);
                        break;
                    case 4:
                        strcpy(bezci[i - 1].stat, udaj);
                        break;
                    case 5:
                        strcpy(bezci[i - 1].oddil, udaj);
                        break;
                    case 6:
                        bezci[i - 1].cas = nactiCas(udaj);
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

// Provede výpis dat do tabulky na obrazovku
void vypisNaObrazovku(const BEZEC *bezci, int pocet) {
    char casText[10];
    int pocetCechu = 0;
    BEZEC b;
    BEZEC nejstarsi = bezci[0];

    printf("S T A R T O V N I  L I S T I N A  -  M A R A T O N\n");
    printf("--------------------------------------------------\n");
    printf("cislo|  prijmeni  |   jmeno    |  narozen  |stat|            klub             |   cas   |\n");
    printf("-----------------------------------------------------------------------------------------\n");

    // Výpis řádků
    for (int i = 0; i < pocet; ++i) {
        b = bezci[i];
        casNaRetezec(casText, b.cas, "%d:%02d:%02d");

        // Celkový počet čechů
        if (strcmp(b.stat, "CZE") == 0) {
            pocetCechu++;
        }

        // Zjistí nejstaršího závodníka
        if (jeStarsi(b.narozeni, nejstarsi.narozeni)) {
            nejstarsi = b;
        }

        printf("  %3d| %11s| %11s| %02d.%02d.%4d| %3s| %28s|  %s|\n", b.cislo, b.prijmeni, b.jmeno, b.narozeni.den,
               b.narozeni.mesic, b.narozeni.rok, b.stat, b.oddil, casText);
    }
    printf("-----------------------------------------------------------------------------------------\n");
    printf("Celkovy pocet zavodniku je %d.\n", pocet);
    printf("Cechu je %d.\n", pocetCechu);
    printf("Nejstarsim zavodnikem je %s %s narozen v roce %d. Je mu %d let.\n", nejstarsi.prijmeni, nejstarsi.jmeno,
           nejstarsi.narozeni.rok, vekBezce(nejstarsi));
}

// Zapíše tabulku do výstupního souboru
void zapisDoSouboru(const BEZEC *bezci, int pocet) {
    FILE *fw = fopen(VYSTUP, "w");
    BEZEC b;
    char casText[10];
    char ztrataText[10];
    CAS ztrata;

    if (fw == NULL) {
        printf("Chyba pri otevirani souboru %s.\n", VYSTUP);
        exit(EXIT_FAILURE);
    }

    fprintf(fw, "V Y S L E D K O V A  L I S T I N A  -  M A R A T O N\n");
    fprintf(fw,
            "---------------------------------------------------------------------------------------------------------\n");
    fprintf(fw,
            "poradi|cislo|  prijmeni  |   jmeno    |  narozen  |stat|            klub             |   cas   | ztrata |\n");
    fprintf(fw,
            "---------------------------------------------------------------------------------------------------------\n");

    // Výpis tabulky do souboru
    for (int i = 0; i < pocet; ++i) {
        b = bezci[i];
        ztrata = sekundyNaCas(casNaSekudy(b.cas) - casNaSekudy(bezci[0].cas));
        casNaRetezec(casText, b.cas, "%d:%02d:%02d");
        casNaRetezec(ztrataText, ztrata, "%d:%02d:%02d");

        fprintf(fw, "%2d.|     %3d|  %10s| %11s| %02d.%02d.%d| %3s| %28s|  %s|%s%s|\n", i + 1, b.cislo, b.prijmeni,
                b.jmeno, b.narozeni.den, b.narozeni.mesic, b.narozeni.rok, b.stat, b.oddil, casText, i == 0 ? "" : "+",
                i == 0 ? "        " : ztrataText);
    }

    fprintf(fw,
            "---------------------------------------------------------------------------------------------------------\n");

    if (fclose(fw) == EOF) {
        printf("Chyba pri uzavirani souboru %s.\n", VYSTUP);
        exit(EXIT_FAILURE);
    }
}

int main() {
    BEZEC bezci[POCET_BEZCU];
    int pocet;

    // Načtení dat do pole struktur a následné testování
    pocet = nactiData(bezci);
    if (pocet != POCET_BEZCU) {
        printf("Nekde se stala chyba pri nacitani dat.\n");
        exit(EXIT_FAILURE);
    }

    // Výpis na obrazovku
    vypisNaObrazovku(bezci, pocet);

    // Seřadí pole
    serad(bezci, pocet);

    // Vypíše tabulku do výstupního souboru
    zapisDoSouboru(bezci, pocet);
    return 0;
}
