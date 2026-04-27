#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Konstanty
#define VSTUP "datalog.csv"
#define VYSTUP "data.html"
#define POCET_ZAZNAMU 20
#define DELKA_RADKU 200
#define ODDELOVAC " "

// Struktura času
typedef struct {
    int hodiny;
    int minuty;
} CAS;

// Struktura záznamu
typedef struct {
    char pc[4];
    CAS pripojen;
    CAS odpojen;
    int prenesenaData;
} ZAZNAM;

// Získá čas z řetězce
CAS nactiCas(const char *retezec) {
    CAS cas;
    sscanf(retezec, "%d:%d", &cas.hodiny, &cas.minuty);
    return cas;
}

// Vrátí výsledek odečtených časů v minutách
// Jako první se uvádí větší čas (čas ukončení připojení)
int casovyRozdilMinuty(CAS konec, CAS zacatek) {
    int minutyKonec = (konec.hodiny * 60) + konec.minuty;
    int minutyZacatek = (zacatek.hodiny * 60) + zacatek.minuty;

    int rozdil = minutyKonec - minutyZacatek;

    // Pokud je rozdíl záporný, znamená to, že konec byl až druhý den
    // Přidáme tedy 1440 minut (24 hodin * 60 minut)
    if (rozdil < 0) {
        rozdil += 1440;
    }

    return rozdil;
}

// Načte data ze vstupního souboru
int nactiData(ZAZNAM *zaznamy) {
    FILE *fr = fopen(VSTUP, "r");
    char radek[DELKA_RADKU];
    char *udaj;
    int pocet;
    int i = 0;

    if (fr == NULL) {
        printf("Chyba pri otevirani souboru %s.\n", VSTUP);
        exit(EXIT_FAILURE);
    }

    // Načtení dat
    while (fgets(radek, DELKA_RADKU, fr) != NULL) {
        udaj = strtok(radek, ODDELOVAC);
        pocet = 0;

        while (udaj != NULL) {
            switch (pocet) {
                case 0:
                    strcpy(zaznamy[i].pc, udaj);
                    break;
                case 1:
                    zaznamy[i].pripojen = nactiCas(udaj);
                    break;
                case 2:
                    zaznamy[i].odpojen = nactiCas(udaj);
                    break;
                case 3:
                    zaznamy[i].prenesenaData = atoi(udaj);
                    break;
                default:
                    break;
            }
            pocet++;
            udaj = strtok(NULL, ODDELOVAC);
        }
        i++;
    }

    if (fclose(fr) == EOF) {
        printf("Chyba pri uzavirani souboru %s.\n", VSTUP);
        exit(EXIT_FAILURE);
    }
    return i;
}

// Vymění parametry
void vymen(ZAZNAM *z1, ZAZNAM *z2) {
    ZAZNAM doc = *z1;
    *z1 = *z2;
    *z2 = doc;
}

// Setřídí pole pomocí algoritmu bubble sort
void setrid(ZAZNAM *zaznamy, int pocet) {
    int i, j;
    ZAZNAM doc;
    int vymena;

    for (i = 0; i < pocet - 1; ++i) {
        vymena = 0;
        for (j = 0; j < pocet - i - 1; ++j) {
            // Porovnáme názvy PC pomocí strcmp (vzestupně)
            int cmp = strcmp(zaznamy[j].pc, zaznamy[j + 1].pc);

            // Podmínka pro prohození
            if (cmp > 0 || (cmp == 0 && zaznamy[j].prenesenaData < zaznamy[j + 1].prenesenaData)) {
                // Prohození záznamů
                doc = zaznamy[j];
                zaznamy[j] = zaznamy[j + 1];
                zaznamy[j + 1] = doc;

                vymena = 1;
            }
        }
        if (vymena == 0) {
            break;
        }
    }
}

// Vypíše tabulku s daty do konzole
void vypisDoKonzole(const ZAZNAM *zaznamy, int pocet) {
    ZAZNAM zaznamyKopie[POCET_ZAZNAMU];

    // Pomocné proměnné
    CAS pripojen, odpojen;
    int dobaPripojeni;

    // Kopírování pole
    memcpy(zaznamyKopie, zaznamy, pocet * sizeof(ZAZNAM));

    // Setřídí pole
    setrid(zaznamyKopie, pocet);

    // Hlavička
    printf("KONTROLNI VYPIS SETRIDENYCH DAT\n\n");

    // Výpis dat
    for (int i = 0; i < pocet; ++i) {
        pripojen = zaznamyKopie[i].pripojen;
        odpojen = zaznamyKopie[i].odpojen;
        dobaPripojeni = casovyRozdilMinuty(odpojen, pripojen);

        printf(" %3s %2d:%02d %2d:%02d  %2d  %7d\n", zaznamyKopie[i].pc, pripojen.hodiny, pripojen.minuty,
               odpojen.hodiny,
               odpojen.minuty, dobaPripojeni, zaznamyKopie[i].prenesenaData);
    }
}

// Vytvoří HTML tabulku se setříděnými údaji a souhrny
void vypisDoSouboru(const ZAZNAM *zaznamy, int pocet) {
    FILE *fw = fopen(VYSTUP, "w");
    ZAZNAM zaznamyKopie[POCET_ZAZNAMU];

    if (fw == NULL) {
        printf("Chyba pri otevirani souboru %s.\n", VYSTUP);
        exit(EXIT_FAILURE);
    }

    // Zkopírování a setřídění pole
    memcpy(zaznamyKopie, zaznamy, pocet * sizeof(ZAZNAM));
    setrid(zaznamyKopie, pocet);

    fprintf(fw, "<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"utf-8\">\n");
    fprintf(fw, "<style>\n");
    fprintf(fw, "  table { border-collapse: collapse; font-family: sans-serif; }\n");
    fprintf(fw, "  th, td { padding: 4px 8px; text-align: right; }\n");
    fprintf(fw, "  th { text-align: left; font-style: italic; }\n");
    fprintf(fw, "  .pc-nazev { text-align: left; font-weight: bold; }\n");
    fprintf(fw, "  .souhrn { background-color: #ADD8E6; } /* Světle modrá barva */\n");
    fprintf(fw, "</style>\n</head>\n<body>\n");

    fprintf(fw, "<table>\n");
    fprintf(fw, "  <tr><th>pc</th><th>start</th><th>konec</th><th>minuty</th><th>data</th></tr>\n");

    int i = 0;
    while (i < pocet) {
        int j = i;
        long celkovaData = 0;
        int celkoveMinuty = 0;

        // Vnitřní cyklus: Najde všechny záznamy pro aktuální PC a spočítá součty
        while (j < pocet && strcmp(zaznamyKopie[i].pc, zaznamyKopie[j].pc) == 0) {
            celkoveMinuty += casovyRozdilMinuty(zaznamyKopie[j].odpojen, zaznamyKopie[j].pripojen);
            celkovaData += zaznamyKopie[j].prenesenaData;
            j++;
        }

        // Tisk souhrnného řádku (světle modrý)
        fprintf(fw, "  <tr class=\"souhrn\">\n");
        fprintf(fw, "    <td class=\"pc-nazev\">%s</td>\n", zaznamyKopie[i].pc);
        fprintf(fw, "    <td></td><td></td>\n"); // Prázdné buňky pro start a konec
        fprintf(fw, "    <td>%d min</td>\n", celkoveMinuty);
        fprintf(fw, "    <td>%ld b</td>\n", celkovaData);
        fprintf(fw, "  </tr>\n");

        // Tisk jednotlivých řádků pro dané PC
        for (int k = i; k < j; k++) {
            int doba = casovyRozdilMinuty(zaznamyKopie[k].odpojen, zaznamyKopie[k].pripojen);

            fprintf(fw, "  <tr>\n");
            fprintf(fw, "    <td></td>\n");
            fprintf(fw, "    <td>%d:%02d</td>\n", zaznamyKopie[k].pripojen.hodiny, zaznamyKopie[k].pripojen.minuty);
            fprintf(fw, "    <td>%d:%02d</td>\n", zaznamyKopie[k].odpojen.hodiny, zaznamyKopie[k].odpojen.minuty);
            fprintf(fw, "    <td>%d min</td>\n", doba);
            fprintf(fw, "    <td>%d b</td>\n", zaznamyKopie[k].prenesenaData);
            fprintf(fw, "  </tr>\n");
        }

        i = j;
    }

    fprintf(fw, "</table>\n");
    fprintf(fw, "</body>\n</html>\n");

    if (fclose(fw) == EOF) {
        printf("Chyba pri uzavirani souboru %s.\n", VYSTUP);
        exit(EXIT_FAILURE);
    }

    printf("\nByl vytvoren soubor %s.\n", VYSTUP);
}

int main(void) {
    ZAZNAM zaznamy[POCET_ZAZNAMU];
    int pocet;

    // Načte a otestuje získaná data
    pocet = nactiData(zaznamy);
    if (pocet != POCET_ZAZNAMU) {
        printf("Chyba pri nacitani dat ze souboru %s.\n", VSTUP);
        exit(EXIT_FAILURE);
    }

    // Výpisy
    vypisDoKonzole(zaznamy, pocet);
    vypisDoSouboru(zaznamy, pocet);
    return 0;
}
