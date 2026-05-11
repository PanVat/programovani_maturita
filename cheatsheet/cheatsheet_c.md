# Návod pro C

---

### Základní konstanty
```
#define VSTUP "beh.txt"
#define VYSTUP "vysledkova_listina.txt"
#define DELKA_RADKU 200
#define POCET_BEZCU 22
#define ODDELOVAC ";"
```

### Načtení dat ze souboru
```
int nactiData(ZAVODNIK *zavodnici) {
    FILE *fr = fopen(VSTUP, "r");
    char radek[DELKA_RADKU];
    char *udaj;
    int pocet = 0;
    int i = 0;

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
                    ...
                }
                udaj = strtok(NULL, ODDELOVAC);
                pocet++;
            }
        }
        i++;
    }
    return i - 1;
}
```

### Vyparsování dat z řetězce do struktury
```
CAS nactiCas(const char *retezec) {
    CAS cas;
    sscanf(retezec, "%d:%d:%d", &cas.hodiny, &cas.minuty, &cas.sekundy);
    return cas;
}
```

### Převedení struktury na řetězec
```
void casNaRetezec(char *retezec, CAS cas, const char *format) {
    sprintf(retezec, format, cas.hodiny, cas.minuty, cas.sekundy);
}
```

### Převedení setin na strukturu času
```
CAS desetinyNaCas(int desetiny) {
    CAS cas;
    cas.hodiny = desetiny / 36000;
    cas.minuty = (desetiny % 36000) / 600;
    cas.sekundy = (desetiny % 600) / 10;
    cas.desetiny = desetiny % 10;
    return cas;
}
```
### Výpočet věku ze systémového času
```
int vekBezce(BEZEC bezec) {
    time_t ted = time(NULL);
    struct tm *aktualniCas = localtime(&ted);

    return (aktualniCas->tm_year + 1900) - bezec.narozeni.rok;
}
```

### Bubble sort
```
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
``` 

### Hlavní funkce
```
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
```