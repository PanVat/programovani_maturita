#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Konstanty
#define VSTUP "jizerska50.txt"
#define VYSTUP "vysledkova_listina.txt"
#define POCET_BEZCU 54
#define DELKA_RADKU 200
#define ODDELOVACE ";,()"

// Údaje o čase
typedef struct {
    int hodiny;
    int minuty;
    int sekundy;
} CAS;

// Údaje o jednotlivém běžci
typedef struct {
    int cislo;
    char prijmeni[30];
    char jmeno[20];
    int rocnik;
    char narodnost[4];
    CAS cas;
} BEZEC;

// Z řetězce načte čas do struktury, kterou vrátí
CAS nactiCas(const char *retezec) {
    CAS cas;
    sscanf(retezec, "%d:%d:%d", &cas.hodiny, &cas.minuty, &cas.sekundy);
    return cas;
}

// Zjistí a vrátí věk běžce
int vekBezce(BEZEC bezec) {
    time_t momentalne = time(NULL);
    struct tm *ted = localtime(&momentalne);

    return (ted->tm_year + 1900) - bezec.rocnik;
}

// Převede strukturu času na sekundy, které vrátí
int casNaSekundy(CAS cas) {
    return (cas.hodiny * 3600) + (cas.minuty * 60) + cas.sekundy;
}

// Vymění parametry
void vymenim(BEZEC *b1, BEZEC *b2) {
    BEZEC b3 = *b1;
    *b1 = *b2;
    *b2 = b3;
}

// Seřazení běžců podle času pomocí algoritmu bubble sort
void serad(BEZEC *bezci, int pocet) {
    int i, j;
    int vymena;
    for (i = 0; i < pocet - 1; i++) {
        vymena = 0;
        for (j = 0; j < pocet - i - 1; j++) {
            if (casNaSekundy(bezci[j].cas) > casNaSekundy(bezci[j + 1].cas)) {
                vymenim(&bezci[j], &bezci[j + 1]);
                vymena = 1;
            }
        }
        if (vymena == 0)
            break;
    }
}

// Ze sekund předaných v parametru vytvoří strukturu CAS, kterou vrátí
CAS sekundyNaCas(int sekundy) {
    CAS cas;
    cas.hodiny = sekundy / 3600;
    cas.minuty = (sekundy % 3600) / 60;
    cas.sekundy = sekundy % 60;
    return cas;
}

// Čas vyextrahuje do řetězce, který vrátí v parametru
void casNaRetezec(char *retezec, CAS cas) {
    sprintf(retezec, "%d:%02d:%02d", cas.hodiny, cas.minuty, cas.sekundy);
}

// Načtení dat ze vstupního souboru do pole struktur
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

    // Načtení jednotlivých dat pomocí smyčky
    while (fgets(radek, DELKA_RADKU, fr) != NULL) {
        if (i > 0) {
            udaj = strtok(radek, ODDELOVACE);
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
                        bezci[i - 1].rocnik = atoi(udaj);
                        break;
                    case 4:
                        strcpy(bezci[i - 1].narodnost, udaj);
                        break;
                    case 5:
                        bezci[i - 1].cas = nactiCas(udaj);
                        break;
                    default:
                        break;
                }
                udaj = strtok(NULL, ODDELOVACE);
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

// Zobrazí tabulku běžců do konzole
void vypisDoKonzole(const BEZEC *bezci, int pocet) {
    BEZEC b;
    BEZEC nejmladsi = bezci[0];
    int pocetCechu = 0;

    // Hlavička tabulky
    printf("S T A R T O V N I  L I S T I N A - J I Z E R S K A   50\n");
    printf("-------------------------------------------------------\n");
    printf("startovni cislo     prijmeni          jmeno rocnik stat\n");
    printf("-------------------------------------------------------\n");

    // Výpis každého řádku údajů o běžci
    for (int i = 0; i < pocet; ++i) {
        b = bezci[i];

        // Počítání Čechů
        if (strcmp(b.narodnost, "CZE") == 0) pocetCechu++;

        // Nejmladší závodník
        if (vekBezce(b) < vekBezce(nejmladsi)) {
            nejmladsi = b;
        }

        printf("            %3d %12s %15s  %4d  %3s\n", b.cislo, b.prijmeni, b.jmeno, b.rocnik, b.narodnost);
    }
    printf("-------------------------------------------------------\n");

    // Statistiky
    printf("Pocet zavodniku: %d.\n", pocet);
    printf("Pocet Cechu    : %d.\n", pocetCechu);
    printf("Nejmladsim zavodnikem je %s %s z %s. Je mu %d let.", nejmladsi.jmeno, nejmladsi.prijmeni,
           nejmladsi.narodnost,
           vekBezce(nejmladsi));
}

// Zapíše tabulku běžců do souboru
void zapisDoSouboru(const BEZEC *bezci, int pocet) {
    FILE *fw = fopen(VYSTUP, "w");
    BEZEC b;
    int ztrataSekundy;
    CAS ztrataCas;
    char ztrataText[10];

    if (fw == NULL) {
        printf("Chyba pri otevirani souboru %s.\n", VYSTUP);
        exit(EXIT_FAILURE);
    }

    // Hlavička tabulky
    fprintf(fw, "V Y S L E D K O V A  L I S T I N A - J I Z E R S K A   50\n");
    fprintf(fw, "---------------------------------------------------------\n");
    fprintf(fw, "poradi cislo     prijmeni          jmeno rocnik stat     cas   ztrata\n");
    fprintf(fw, "---------------------------------------------------------------------\n");

    // Výpis každého řádku údajů o běžci
    for (int i = 0; i < pocet; ++i) {
        b = bezci[i];

        // Výpočet ztráty
        ztrataSekundy = casNaSekundy(b.cas) - casNaSekundy(bezci[0].cas);
        ztrataCas = sekundyNaCas(ztrataSekundy);

        // Vložení času do řetězce pro snadnější výpis
        casNaRetezec(ztrataText, ztrataCas);

        fprintf(fw, "   %2d.   %3d %12s %15s  %4d  %3s %d:%02d:%02d %s%s\n", i + 1, b.cislo, b.prijmeni,
                b.jmeno,
                b.rocnik, b.narodnost, b.cas.hodiny, b.cas.minuty, b.cas.sekundy, i == 0 ? " " : "+",
                i == 0 ? "     " : ztrataText);
    }
    fprintf(fw, "---------------------------------------------------------------------\n");

    if (fclose(fw) == EOF) {
        printf("Chyba pri uzavirani souboru %s.\n", VYSTUP);
        exit(EXIT_FAILURE);
    }
}

int main() {
    BEZEC bezci[POCET_BEZCU];
    int pocet;

    // Načtení dat do pole struktur BEZEC
    pocet = nactiData(bezci);

    // Test, jestli se data správně načetla
    if (pocet != POCET_BEZCU) {
        printf("Nekde se stala chyba pri nacitani dat ze souboru %s.\n", VSTUP);
        exit(EXIT_FAILURE);
    }

    // Výpis tabulky do konzole
    vypisDoKonzole(bezci, pocet);

    // Seřadí běžce v poli
    serad(bezci, pocet);

    // Zápis tabulky do souboru
    zapisDoSouboru(bezci, pocet);
    return 0;
}
