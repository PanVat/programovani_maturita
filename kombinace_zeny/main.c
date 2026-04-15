#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Konstanty
#define VSTUP "startovni_listina_kombinace_zeny.txt"
#define VYSTUP "vysledkova_listina_kombinace_zeny.txt"
#define DELKA_RADKU 200
#define POCET_ZAVODNIC 10
#define ODDELOVAC " "

// Informace o čase
typedef struct {
    int minuty;
    int sekundy;
    int setiny;
} CAS;

// Struktura uchovávající informace o závodnici
typedef struct {
    int cislo;
    char jmeno[15];
    char prijmeni[20];
    char stat[4];
    CAS sjezd;
    CAS slalom;
} ZAVODNICE;

// Načte čas sjezdu v řetězci do struktury CAS
CAS nactiCasSjezd(const char *retezec) {
    CAS cas;
    sscanf(retezec, "%d:%d,%d", &cas.minuty, &cas.sekundy, &cas.setiny);
    return cas;
}

// Načte čas slalomu v řetězci do struktury CAS
CAS nactiCasSlalom(const char *retezec) {
    CAS cas = {0}; // Nulová hodnota kvůli minutám, které by jinak byly nedefinované
    sscanf(retezec, "%d,%d", &cas.sekundy, &cas.setiny);
    return cas;
}

// Získá počet setin ze struktury času
int casNaSetiny(CAS cas) {
    return (cas.minuty * 6000) + (cas.sekundy * 100) + cas.setiny;
}

// Převede setiny předané parametrem na strukturu času, kterou vrátí
CAS setinyNaCas(int setiny) {
    CAS cas;
    cas.minuty = setiny / 6000;
    cas.sekundy = (setiny % 6000) / 100;
    cas.setiny = setiny % 100;
    return cas;
}

// Vrátí součet dvou časů
int soucetCasu(CAS c1, CAS c2){
    return casNaSetiny(c1) + casNaSetiny(c2);
}

// Vymění parametry
void vymenim(ZAVODNICE *z1, ZAVODNICE *z2){
    ZAVODNICE z3 = *z1;
    *z1 = *z2;
    *z2 = z3;
}

// Setřídí pole struktur pomocí algoritmu bubble sort
void setrid(ZAVODNICE *zavodnice, int pocet){
    int i, j;
    int vymena;
    for (i = 0; i < pocet - 1; i++) {
        vymena = 0;
        for (j = 0; j < pocet - i - 1; j++) {
            if (soucetCasu(zavodnice[j].sjezd, zavodnice[j].slalom) > soucetCasu(zavodnice[j + 1].sjezd, zavodnice[j + 1].slalom)) {
                vymenim(&zavodnice[j], &zavodnice[j + 1]);
                vymena = 1;
            }
        }
        if (vymena == 0)
            break;
    }
}

// Otevře vstupní soubor a načte jeho data do pole struktur
int nactiData(ZAVODNICE *zavodnice) {
    FILE *fr = fopen(VSTUP, "r");
    char radek[DELKA_RADKU];
    char *udaj;
    int pocet;
    int i = 0;

    if (fr == NULL) {
        printf("Chyba pri otevirani souboru %s.\n", VSTUP);
        exit(EXIT_FAILURE);
    }

    // Načtení jednotlivých dat
    while (fgets(radek, DELKA_RADKU, fr) != NULL) {
        udaj = strtok(radek, ODDELOVAC);
        pocet = 0;
        while (udaj != NULL) {
            switch (pocet) {
                case 0:
                    zavodnice[i].cislo = atoi(udaj);
                    break;
                case 1:
                    strcpy(zavodnice[i].jmeno, udaj);
                    break;
                case 2:
                    strcpy(zavodnice[i].prijmeni, udaj);
                    break;
                case 3:
                    strcpy(zavodnice[i].stat, udaj);
                    break;
                case 4:
                    zavodnice[i].sjezd = nactiCasSjezd(udaj);
                    break;
                case 5:
                    zavodnice[i].slalom = nactiCasSlalom(udaj);
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

// Vypíše tabulku s daty do souboru
void zapisDoSouboru(const ZAVODNICE *zavodnice, int pocet) {
    ZAVODNICE z;
    FILE *fw = fopen(VYSTUP, "w");
    CAS celkemNejrychlejsi;
    CAS celkem;
    CAS ztrata;
    int soucetSetin;

    if (fw == NULL) {
        printf("Chyba pri otevirani souboru %s.\n", VYSTUP);
        exit(EXIT_FAILURE);
    }

    printf("\nSoubor %s byl vytvoren.\n", VYSTUP);

    // Záhlaví tabulky
    fprintf(fw,"A L P S K E  L Y Z O V A N I - K O M B I N A C E  Z E N Y\n");
    fprintf(fw,"---------------------------------------------------------\n");
    fprintf(fw,"poradi      jmeno        prijmeni stat    sjezd slalom   celkem   ztrata\n");
    fprintf(fw,"------------------------------------------------------------------------\n");

    celkemNejrychlejsi = setinyNaCas(casNaSetiny(zavodnice[0].sjezd) + casNaSetiny(zavodnice[0].slalom));

    // Hlavní smyčka, která vypíše jednotlivé řádky s daty
    for (int i = 0; i < pocet; ++i) {
        z = zavodnice[i];
        celkem = setinyNaCas(casNaSetiny(z.sjezd) + casNaSetiny(z.slalom));
        ztrata = setinyNaCas(casNaSetiny(celkem) - casNaSetiny(celkemNejrychlejsi));

        fprintf(fw,"    %2d.  %9s  %14s  %3s  %d:%02d,%02d  %02d,%02d  %d:%02d,%02d  %d:%02d,%02d\n", i + 1, z.jmeno,
               z.prijmeni, z.stat,
               z.sjezd.minuty, z.sjezd.sekundy, z.sjezd.setiny, z.slalom.sekundy, z.slalom.setiny, celkem.minuty,
               celkem.sekundy, celkem.setiny, ztrata.minuty, ztrata.sekundy, ztrata.setiny);
    }

    if (fclose(fw) == EOF) {
        printf("Chyba pri uzavirani souboru %s.\n", VYSTUP);
        exit(EXIT_FAILURE);
    }
}

// Vypíše tabulku s daty do konzole
void vypisDoKonzole(const ZAVODNICE *zavodnice, int pocet) {
    ZAVODNICE z;

    // Hlavička tabulky
    printf("Alpske lyzovani startovni listina K O M B I N A C E  Z E N Y\n");
    printf("------------------------------------------------------------\n");
    printf("startovni cislo      jmeno        prijmeni stat    sjezd slalom\n");
    printf("---------------------------------------------------------------\n");

    // Smyčka pro vypsání každého řádku
    for (int i = 0; i < pocet; ++i) {
        z = zavodnice[i];

        printf("             %2d  %9s  %14s  %3s  %d:%02d,%02d  %02d,%02d\n", z.cislo, z.jmeno, z.prijmeni, z.stat,
               z.sjezd.minuty, z.sjezd.sekundy, z.sjezd.setiny, z.slalom.sekundy, z.slalom.setiny);
    }
}

int main() {
    ZAVODNICE zavodnice[POCET_ZAVODNIC];
    int pocet;

    // Načtení dat
    pocet = nactiData(zavodnice);

    // Kontrola načtených dat
    if (pocet != POCET_ZAVODNIC) {
        printf("Nekde se stala chyba pri nacitani ze souboru %s.\n", VSTUP);
        exit(EXIT_FAILURE);
    }

    // Výpis tabulky do konzole
    vypisDoKonzole(zavodnice, pocet);

    // Setřídí pole podle celkového času závodnic
    setrid(zavodnice, pocet);

    // Zápis tabulky s výsledky do výstupního souboru
    zapisDoSouboru(zavodnice, pocet);
    return 0;
}
