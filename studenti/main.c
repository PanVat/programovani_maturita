#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Konstanty
#define VSTUP "seznam.txt"
#define VYSTUP "vypis_studentu.htm"
#define ODDELOVAC ";"
#define POCET_STUDENTU 8
#define DELKA_RADKU 200

// Struktura obsahující datum
typedef struct {
    int den;
    int mesic;
    int rok;
} DATUM;

// Struktura uchovávající informace o studentovi
typedef struct {
    char jmeno[10];
    char prijmeni[20];
    char pohlavi[2];
    DATUM narozeni;
    int absence;
} STUDENT;

// Převede datum z řetězce na strukturu DATUM
DATUM datumZRetezce(const char *retezec) {
    DATUM datum;
    sscanf(retezec, "%d.%d.%d", &datum.den, &datum.mesic, &datum.rok);
    return datum;
}

void retezecZData(char *retezec, DATUM datum) {
    sprintf(retezec, "%d-%d-%d", datum.rok, datum.mesic, datum.den);
}

// Načte data ze souboru do pole struktur STUDENT
int nactiData(STUDENT *studenti) {
    FILE *fr = fopen(VSTUP, "r");
    char radek[DELKA_RADKU];
    char *udaj;
    int pocet;
    int i = 0;

    if (fr == NULL) {
        printf("Chyba pri otevirani souboru %s.\n", VSTUP);
        exit(EXIT_FAILURE);
    }

    while (fgets(radek, DELKA_RADKU, fr) != NULL) {
        if (i > 0) {
            udaj = strtok(radek, ODDELOVAC);
            pocet = 0;

            while (udaj != NULL) {
                switch (pocet) {
                    case 0:
                        strcpy(studenti[i - 1].jmeno, udaj);
                        break;
                    case 1:
                        strcpy(studenti[i - 1].prijmeni, udaj);
                        break;
                    case 2:
                        strcpy(studenti[i - 1].pohlavi, udaj);
                        break;
                    case 3:
                        studenti[i - 1].narozeni = datumZRetezce(udaj);
                        break;
                    case 4:
                        studenti[i - 1].absence = atoi(udaj);
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

// Zjistí, jestli je student žena
int jeZena(STUDENT student) {
    return strcmp(student.pohlavi, "Z") == 0;
}

// Vypíše statistiky do konzole
void vypisStatistiky(const STUDENT *studenti, int pocet) {
    int pocetZen = 0;
    STUDENT nejvetsiAbsence = studenti[0];

    // Logika
    for (int i = 0; i < pocet; i++) {
        if (studenti[i].absence > nejvetsiAbsence.absence) {
            nejvetsiAbsence = studenti[i];
        }
        if (jeZena(studenti[i])) {
            pocetZen++;
        }
    }

    // Výpisy
    printf("Pocet zaznamu v souboru je %d.\n", pocet);
    printf("Pocet zen je %d.\n", pocetZen);
    printf("Pocet muzu je %d.\n", pocet - pocetZen);
    printf("Student s nejvetsi absenci %d hodin je %s %s.\n", nejvetsiAbsence.absence, nejvetsiAbsence.jmeno,
           nejvetsiAbsence.prijmeni);
}

// Vytvoří a vrátí rodné číslo bez lomítka na základě data narození (RRRR-mm-dd)
int vratRodneCislo(STUDENT student) {
    char datum[11];
    char den[3];
    char mesic[3];
    char rok[3];
    char rodneCislo[7];
    int mesicZena;

    retezecZData(datum, student.narozeni);

    // Rok
    strncpy(rok, datum + 2, 2);
    rok[2] = '\0';

    // Mesic
    strncpy(mesic, datum + 5, 2);
    mesic[2] = '\0';

    if (jeZena(student)) {
        mesicZena = atoi(mesic) + 50;
        sprintf(mesic, "%d", mesicZena);
        mesic[2] = '\0';
    }

    // Den
    strncpy(den, datum + 8, 2);
    den[2] = '\0';

    // Poskládání rodného čísla
    sprintf(rodneCislo, "%02d%02d%02d", atoi(rok), atoi(mesic), atoi(den));

    return atoi(rodneCislo);
}

// Vytvoří HTML tabulku do výstupního souboru
void vytvorTabulku(const STUDENT *studenti, int pocet) {
    FILE *fw = fopen(VYSTUP, "w");
    int aktualniRodneCislo;

    if (fw == NULL) {
        printf("Chyba pri otevirani souboru %s.\n", VYSTUP);
        exit(EXIT_FAILURE);
    }

    printf("\nByl vytvoren soubor %s.\n", VYSTUP);

    fprintf(fw, "<h1>Seznam studentu</h1>\n");
    fprintf(fw, "<table>\n");

    // Hlavička
    fprintf(fw, "<tr>\n");
    fprintf(fw, "<th>jmeno</th>\n");
    fprintf(fw, "<th>prijmeni</th>\n");
    fprintf(fw, "<th>muz/zena</th>\n");
    fprintf(fw, "<th>rodne cislo</th>\n");
    fprintf(fw, "</tr>\n");

    // Výpis dat
    for (int i = 0; i < pocet; i++) {
        aktualniRodneCislo = vratRodneCislo(studenti[i]);
        fprintf(fw, "<tr>\n");
        fprintf(fw, "<td>%s</td><td>%s</td><td>%s</td><td>%d</td>\n", studenti[i].jmeno, studenti[i].prijmeni,
                studenti[i].pohlavi, aktualniRodneCislo);
        fprintf(fw, "</tr>\n");
    }
    fprintf(fw, "</table>\n");

    if (fclose(fw) == EOF) {
        printf("Chyba pri uzavirani souboru %s.\n", VYSTUP);
        exit(EXIT_FAILURE);
    }
}

int main(void) {
    STUDENT studenti[POCET_STUDENTU];
    int pocet;

    // Načtení studentů do pole struktur
    pocet = nactiData(studenti);
    if (pocet != POCET_STUDENTU) {
        printf("Chyba pri nacitani dat ze souboru %s.\n", VSTUP);
        exit(EXIT_FAILURE);
    }

    // Výpisy
    vypisStatistiky(studenti, pocet);
    vytvorTabulku(studenti, pocet);
    return 0;
}