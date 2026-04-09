#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Konstanty
#define VSTUP "skoky.txt"
#define VYSTUP "skoky.html"
#define POCET_ZAVODNIKU 60
#define DELKA_RADKU 200
#define ODDELOVAC ";"

// Struktura uchovávající datum
typedef struct {
    int den;
    int mesic;
    int rok;
} DATUM;

// Struktura uchovávající informace o závodníkovi
typedef struct {
    char prijmeni[20];
    char jmeno[20];
    DATUM datumNarozeni;
    char stat[4];
    int delka;
    char tymy[4];
} ZAVODNIK;

DATUM nactiDatum(const char *retezec) {
    DATUM datum;
    sscanf(retezec, "%d.%d.%d", &datum.den, &datum.mesic, &datum.rok);
    return datum;
}

// Načte data ze souboru skoky.txt do pole struktur ZAVODNIK
int nactiData(ZAVODNIK *zavodnici) {
    FILE *fr = fopen(VSTUP, "r");
    char radek[DELKA_RADKU];
    char *udaj;
    int pocet = 0;
    int i = 0;

    if (fr == NULL) {
        printf("Soubor %s se nepodarilo otevrit.\n", VSTUP);
        exit(EXIT_FAILURE);
    }

    while (fgets(radek, DELKA_RADKU, fr) != NULL) {
        // Odstranění newline znaku z celého řádku
        int len = strlen(radek);
        if (len > 0 && radek[len - 1] == '\n') {
            radek[len - 1] = '\0';
        }

        if (i > 0) {
            udaj = strtok(radek, ODDELOVAC);
            pocet = 0;

            while (udaj != NULL) {
                switch (pocet) {
                    case 0:
                        strcpy(zavodnici[i - 1].prijmeni, udaj);
                        break;
                    case 1:
                        strcpy(zavodnici[i - 1].jmeno, udaj);
                        break;
                    case 2:
                        zavodnici[i - 1].datumNarozeni = nactiDatum(udaj);
                        break;
                    case 3:
                        strcpy(zavodnici[i - 1].stat, udaj);
                        break;
                    case 4:
                        zavodnici[i - 1].delka = atoi(udaj);
                        break;
                    case 5:
                        strcpy(zavodnici[i - 1].tymy, udaj);
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
        printf("Soubor %s se nepodarilo uzavrit.\n", VSTUP);
        exit(EXIT_FAILURE);
    }

    return i - 1;
}

// Převede formát datumu D.M.RRRR na RRRR-MM-DD
void prevedDatum(char *novyFormat, DATUM datum) {
    sprintf(novyFormat, "%d-%02d-%02d", datum.rok, datum.mesic, datum.den);
}

// Vypíše statistiky o závodnících do konzole
void vypisStatistiky(const ZAVODNIK *zavodnici, int pocet) {
    int zavodnikuVTymech = 0;
    ZAVODNIK nejlepsiSkokan = zavodnici[0];
    double celkovaDelka = 0;

    for (int i = 0; i < pocet; ++i) {
        if (strcmp(zavodnici[i].tymy, "ANO") == 0) {
            zavodnikuVTymech++;
            celkovaDelka += zavodnici[i].delka;
        }
        if (zavodnici[i].delka > nejlepsiSkokan.delka) {
            nejlepsiSkokan = zavodnici[i];
        }
    }

    printf("Pocet zavodniku je %d.\n", pocet);
    printf("Pocet zavodniku nezarazenych v tymech je %d.\n", pocet - zavodnikuVTymech);
    printf("Nejdelsi skok %d metru dosahl %s %s z %s.\n", nejlepsiSkokan.delka, nejlepsiSkokan.jmeno,
           nejlepsiSkokan.prijmeni, nejlepsiSkokan.stat);
    printf("Prumerna delka zavodniku zarazenych v tymech je %.2f metru.\n", celkovaDelka / zavodnikuVTymech);
}

// Vytvoří HTML soubor s tabulkou
void zapisDoSouboru(ZAVODNIK *zavodnici, int pocet) {
    FILE *fw = fopen(VYSTUP, "w");
    char noveDatum[11];
    int j = 0;

    if (fw == NULL) {
        printf("Soubor %s se nepodarilo otevrit.\n", VYSTUP);
        exit(EXIT_FAILURE);
    }

    printf("\nByl vytvoren soubor %s.\n", VYSTUP);

    // Styly
    fprintf(fw, "<style>\n");
    fprintf(fw, "td {\n"
                " border: 1px solid black\n;"
                " border-style: dotted;\n"
                "}");
    fprintf(fw, "th {\n"
                "border: none;\n"
                "}");
    fprintf(fw, "</style>\n");

    // Tabulka
    fprintf(fw, "<h1>Tym Ceske republiky</h1>\n");
    fprintf(fw, "<table>\n");
    fprintf(fw, "<tr>\n");
    fprintf(fw, "<th>poradove cislo</th>\n");
    fprintf(fw, "<th>jmeno</th>\n");
    fprintf(fw, "<th>prijmeni</th>\n");
    fprintf(fw, "<th>datum narozeni</th>\n");
    fprintf(fw, "<th>delka skoku</th>\n");
    fprintf(fw, "</tr>\n");
    for (int i = 0; i < pocet; ++i) {
        if (strcmp(zavodnici[i].stat, "CZE") == 0 && strcmp(zavodnici[i].tymy, "ANO") == 0) {
            j += 1;
            fprintf(fw, "<tr>\n");
            prevedDatum(noveDatum, zavodnici[i].datumNarozeni);
            fprintf(fw, "<td>%d.</td><td>%s</td><td>%s</td><td>%s</td><td>%d m</td>\n", j, zavodnici[i].jmeno,
                    zavodnici[i].prijmeni, noveDatum, zavodnici[i].delka);
            fprintf(fw, "</tr>\n");
        }
    }
    fprintf(fw, "</table>\n");

    if (fclose(fw) == EOF) {
        printf("Soubor %s se nepodarilo uzavrit.\n", VYSTUP);
        exit(EXIT_FAILURE);
    }
}

int main() {
    ZAVODNIK zavodnici[POCET_ZAVODNIKU];
    int pocet;

    // Načtení dat ze souboru
    pocet = nactiData(zavodnici);

    // Kontrola správnosti načtení dat
    if (pocet != POCET_ZAVODNIKU) {
        printf("Nekde se stala chyba pri nacitani dat ze souboru %s.\n", VSTUP);
        exit(EXIT_FAILURE);
    }

    // Výpisy
    vypisStatistiky(zavodnici, pocet);
    zapisDoSouboru(zavodnici, pocet);
    return 0;
}
