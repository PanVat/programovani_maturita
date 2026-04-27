#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Konstanty
#define VSTUP "knihy.txt"
#define VYSTUP "vystup_knih.htm"
#define POCET_KNIH 10
#define VELIKOST_RADKU 200
#define ODDELOVAC ";"

// Struktura obsahující informace o knize
typedef struct {
    int id;
    char nazev[25];
    char nosic[10];
    int rok;
    int hmotnost;
    char isbn[25];
} KNIHA;

// Načte data do pole struktur KNIHA
int nactiData(KNIHA *knihy) {
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
        if (i > 0) {
            pocet = 0;
            udaj = strtok(radek, ODDELOVAC);

            while (udaj != NULL) {
                switch (pocet) {
                    case 0:
                        knihy[i - 1].id = atoi(udaj);
                        break;
                    case 1:
                        strcpy(knihy[i - 1].nazev, udaj);
                        break;
                    case 2:
                        strcpy(knihy[i - 1].nosic, udaj);
                        break;
                    case 3:
                        knihy[i - 1].rok = atoi(udaj);
                        break;
                    case 4:
                        knihy[i - 1].hmotnost = atoi(udaj);
                        break;
                    case 5:
                        strcpy(knihy[i - 1].isbn, udaj);
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

// Odstraní pomlčky z ISBN
void odsranPomlcky(KNIHA *kniha) {
    char doc[25];
    strcpy(doc, kniha->isbn);

    int j = 0;
    for (int i = 0; doc[i] != '\0'; ++i) {
        if (doc[i] != '-') {
            kniha->isbn[j] = doc[i];
            j++;
        }
    }
    kniha->isbn[j] = '\0';
}

// Funkce zjistí, jestli je ISBN 10 nebo 13místné
int verzeISBN(KNIHA kniha) {
    odsranPomlcky(&kniha);
    int delka = strlen(kniha.isbn);

    if (delka == 10) {
        return 10;
    }
    if (delka == 13) {
        return 13;
    }
    return 0;
}

// Výpis do souboru HTML
void zapisDoSouboru(KNIHA *knihy, int pocet) {
    FILE *fw = fopen(VYSTUP, "w");

    if (fw == NULL) {
        printf("Chyba pri otevirani souboru %s.\n", VYSTUP);
        exit(EXIT_FAILURE);
    }

    printf("\nByl vytvoren soubor %s.\n", VYSTUP);

    // Odstranění pomlček
    for (int i = 0; i < pocet; i++) {
        odsranPomlcky(&knihy[i]);
    }

    // HTML styly
    fprintf(fw, "<style>\n");
    fprintf(fw, "table {\n"
                "  border-collapse: separate;\n"
                "  border-spacing: 2px;\n"
                "  margin-bottom: 20px;\n"
                "}\n");
    fprintf(fw, "td {\n"
                "  border: 1px dotted black;\n"
                "  padding: 3px;\n"
                "}\n");
    fprintf(fw, "th {\n"
                "  border: none;\n"
                "  text-align: left;\n"
                "  padding: 5px;\n"
                "}\n");
    fprintf(fw, "</style>\n");

    // ISBN-10
    fprintf(fw, "<h1>Seznam knih s ISBN-10</h1>\n");
    fprintf(fw, "<table>\n<tr>\n");
    fprintf(fw, "<th>cislo</th><th>nazev</th><th>nosic</th><th>rok vydani</th><th>hmotnost</th><th>ISBN</th>\n");
    fprintf(fw, "</tr>\n");

    for (int i = 0; i < pocet; ++i) {
        if (verzeISBN(knihy[i]) == 10) {
            fprintf(fw, "<tr><td>%d</td><td>%s</td><td>%s</td><td>%d</td><td>%d</td><td>%s</td></tr>\n",
                    knihy[i].id, knihy[i].nazev, knihy[i].nosic, knihy[i].rok, knihy[i].hmotnost, knihy[i].isbn);
        }
    }
    fprintf(fw, "</table>\n");

    // ISBN-13
    fprintf(fw, "<h1>Seznam knih s ISBN-13</h1>\n");
    fprintf(fw, "<table>\n<tr>\n");
    fprintf(fw, "<th>cislo</th><th>nazev</th><th>nosic</th><th>rok vydani</th><th>hmotnost</th><th>ISBN</th>\n");
    fprintf(fw, "</tr>\n");

    for (int i = 0; i < pocet; ++i) {
        if (verzeISBN(knihy[i]) == 13) {
            fprintf(fw, "<tr><td>%d</td><td>%s</td><td>%s</td><td>%d</td><td>%d</td><td>%s</td></tr>\n",
                    knihy[i].id, knihy[i].nazev, knihy[i].nosic, knihy[i].rok, knihy[i].hmotnost, knihy[i].isbn);
        }
    }
    fprintf(fw, "</table>\n");

    if (fclose(fw) == EOF) {
        printf("Chyba pri uzavirani souboru %s.\n", VYSTUP);
        exit(EXIT_FAILURE);
    }
}

// Výpis do konzole
void vypisNaObrazovku(const KNIHA *knihy, int pocet) {
    int pocetKnih = 0;
    int celkovaHmotnost = 0;
    KNIHA nejnovejsi = knihy[0];

    for (int i = 0; i < pocet; ++i) {
        if (strcmp(knihy[i].nosic, "Kniha") == 0) {
            pocetKnih++;
            celkovaHmotnost += knihy[i].hmotnost;
        }
        if (knihy[i].rok > nejnovejsi.rok) {
            nejnovejsi = knihy[i];
        }
    }
    printf("Pocet zaznamu v souboru je %d.\n", pocet);
    printf("Pocet knih je %d.\n", pocetKnih);
    printf("Pocet dvd je %d.\n", pocet - pocetKnih);
    printf("Celkova hmotnost knih je %d kg a %d g.\n", celkovaHmotnost / 1000, celkovaHmotnost % 1000);
    printf("Nejnovejsi kniha je %s vydana v roce %d.\n", nejnovejsi.nazev, nejnovejsi.rok);
}


int main() {
    KNIHA knihy[POCET_KNIH];
    int pocet;

    // Načtení dat do pole struktur
    pocet = nactiData(knihy);

    // Kontrola načtení všech dat
    if (pocet != POCET_KNIH) {
        printf("Nekde se stala chyba pri nacitani dat ze souboru %s.\n", VSTUP);
        exit(EXIT_FAILURE);
    }

    // Výpisy
    vypisNaObrazovku(knihy, pocet);
    zapisDoSouboru(knihy, pocet);
    return 0;
}
