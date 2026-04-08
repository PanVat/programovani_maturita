#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Konstanty
#define VSTUP "zbozi.txt"
#define VYSTUP "vypis_zbozi.htm"
#define POCET_POLOZEK 11
#define VELIKOST_RADKU 200
#define ODDELOVAC ";"

// Struktura zboží
typedef struct {
    char dodavatel[3];
    char nazev[25];
    int hmotnost;
    int pocet;
    double cena;
} ZBOZI;

// Načtení dat ze souboru
int nactiData(ZBOZI *zbozi) {
    FILE *fr = fopen(VSTUP, "r");
    char radek[VELIKOST_RADKU];
    char *udaj;
    int i = 0;
    int pocet;

    if (fr == NULL) {
        printf("Chyba pri otevirani souboru %s.\n", VSTUP);
        exit(EXIT_FAILURE);
    }

    while (fgets(radek, VELIKOST_RADKU, fr) != NULL) {
        if (i > 0) {
            pocet = 0;
            udaj = strtok(radek, ODDELOVAC);

            while (udaj != NULL) {
                switch (pocet) {
                    case 0:
                        strcpy(zbozi[i - 1].dodavatel, udaj);
                        break;
                    case 1:
                        strcpy(zbozi[i - 1].nazev, udaj);
                        break;
                    case 2:
                        zbozi[i - 1].hmotnost = atoi(udaj);
                        break;
                    case 3:
                        zbozi[i - 1].pocet = atoi(udaj);
                        break;
                    case 4:
                        zbozi[i - 1].cena = atof(udaj);
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

// Výpis tabulky do konzole
void vypisDoKonzole(const ZBOZI *zbozi, int pocet) {
    double celkovaCena;
    double celkovaCenaPolozek = 0;
    int celkovaHmotnost = 0;
    ZBOZI nejdrazsi = zbozi[0];

    printf("U C T E N K A\n");
    printf("dodavatel     nazev zbozi hmotnost pocet    cena       cena\n");
    printf("(zkratka)                 (1 kusu)  kusu (1 kusu)    celkem\n");
    printf("-------------------------------------------------------------\n");

    // Výpis dat uložených v poli struktur zbozi
    for (int i = 0; i < pocet; ++i) {
        celkovaCena = zbozi[i].cena * zbozi[i].pocet;
        celkovaCenaPolozek += celkovaCena;
        celkovaHmotnost += zbozi[i].hmotnost * zbozi[i].pocet;

        if (zbozi[i].cena > nejdrazsi.cena) {
            nejdrazsi = zbozi[i];
        }

        printf("%2s %22s   %4d g   %2d  %5.2f Kc %6.2f Kc\n", zbozi[i].dodavatel, zbozi[i].nazev, zbozi[i].hmotnost,
               zbozi[i].pocet, zbozi[i].cena, celkovaCena);
    }
    // Statistiky
    printf("\n");
    printf("Cena celkem              :%6.2f Kc\n", celkovaCenaPolozek);
    printf("Pocet polozek            :%d\n", pocet);
    printf("Celkova hmotnost zbozi   :%d kg %d g.\n", celkovaHmotnost / 1000, celkovaHmotnost % 1000);
    printf("Nejdrazsi nakoupene zbozi:%s za %5.2f Kc.\n", nejdrazsi.nazev, nejdrazsi.cena);
}

// Výpis tabulky na web
void vypisDoSouboru(const ZBOZI *zbozi, int pocet) {
    FILE *fw = fopen(VYSTUP, "w");

    if (fw == NULL) {
        printf("Chyba pri otevirani souboru %s.\n", VYSTUP);
        exit(EXIT_FAILURE);
    }
    printf("\nByl vytvoren soubor %s.\n", VYSTUP);

    // HTML styly
    fprintf(fw, "<style>\n");
    fprintf(fw, "td {\n"
                " border: 1px solid black\n;"
                " border-style: dotted;\n"
                "}");
    fprintf(fw, "th {\n"
                "border: none;\n"
                "}");
    fprintf(fw, "</style>\n");

    // Výpis HTML tabulky
    fprintf(fw, "<h1>Zbozi od externich dodavatelu</h1>\n");

    fprintf(fw, "<table>\n");
    fprintf(fw, "<tr>\n");

    fprintf(fw, "<th>dodavatel</th>\n");
    fprintf(fw, "<th>nazev</th>\n");
    fprintf(fw, "<th>hmotnost v gramech</th>\n");
    fprintf(fw, "<th>cena 1 kusu v Kc</th>\n");

    // Výpis všech dat
    for (int i = 0; i < pocet; ++i) {
        if (strcmp(zbozi[i].dodavatel, "OP") != 0) {
            fprintf(fw, "<tr><td>%s</td><td>%s</td><td>%d</td><td>%4.2f</td></tr>\n", zbozi[i].dodavatel,
                    zbozi[i].nazev,
                    zbozi[i].hmotnost, zbozi[i].cena);
        }
    }

    fprintf(fw, "</tr>\n");
    fprintf(fw, "</table>");

    if (fclose(fw) == EOF) {
        printf("Chyba pri uzavirani souboru %s.\n", VYSTUP);
        exit(EXIT_FAILURE);
    }
}

int main() {
    ZBOZI zbozi[POCET_POLOZEK];
    int pocet;

    // Načtení dat ze souboru
    pocet = nactiData(zbozi);

    // Kontrola načtených dat
    if (pocet != POCET_POLOZEK) {
        printf("Chyba pri nacitani dat ze souboru %s.\n", VSTUP);
        exit(EXIT_FAILURE);
    }
    // Výpisy
    vypisDoKonzole(zbozi, pocet);
    vypisDoSouboru(zbozi, pocet);
    return 0;
}
