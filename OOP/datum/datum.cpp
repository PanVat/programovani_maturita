#include "datum.h"
#include <ctime>

// Výchozí konstruktor
datum::datum() {
    time_t momentalne = time(nullptr);
    struct tm *ted = localtime(&momentalne);

    this->rok = ted->tm_year + 1900;
    this->mesic = ted->tm_mon + 1;
    this->den = ted->tm_mday;
}

// Parametrický konstruktor
datum::datum(int den, int mesic, int rok) : datum() {
    setDatum(den, mesic, rok);
}

// Kopírovací konstruktor
datum::datum(const datum &dat) {
    this->den = dat.den;
    this->mesic = dat.mesic;
    this->rok = dat.rok;
}

// Vrátí den
int datum::getDen() const {
    return this->den;
}

// Vrátí měsíc
int datum::getMesic() const {
    return this->mesic;
}

// Vrátí rok
int datum::getRok() const {
    return this->rok;
}

// Vrátí datum jako řetězec
string datum::getDatum() const {
    return to_string(den) + ". " + to_string(mesic) + ". " + to_string(rok);
}

// Zjistí, jestli je zadaný rok přestupný
bool datum::jePrestupnyRok(int rok) const {
    return (rok % 4 == 0 && rok % 100 != 0) || (rok % 400 == 0);
}

// Vrátí počet dní v předaném měsíci
int datum::pocetDniVMesici(int mesic) const {
    const int dnyVMesici[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (jePrestupnyRok(this->rok) && mesic == 2) {
        return 29;
    }
    return dnyVMesici[mesic - 1];
}

// Nastaví celé datum - den, měsíc i rok
bool datum::setDatum(int den, int mesic, int rok) {
    if (rok < MIN_ROK || rok > MAX_ROK) return false;
    if (mesic < 1 || mesic > 12) return false;

    int maxDni = 31;
    if (mesic == 4 || mesic == 6 || mesic == 9 || mesic == 11) {
        maxDni = 30;
    } else if (mesic == 2) {
        maxDni = jePrestupnyRok(rok) ? 29 : 28;
    }

    if (den < 1 || den > maxDni) return false;

    this->den = den;
    this->mesic = mesic;
    this->rok = rok;

    return true;
}

// Vrátí celkový počet dní od 1. 1. 1970
long long datum::pocetDniOdEpochy() const {
    long long celkemDni = 0;

    // Přičtení celých let od 1970
    for (int r = MIN_ROK; r < this->rok; ++r) {
        celkemDni += jePrestupnyRok(r) ? 366 : 365;
    }

    // Přičtení dnů v měsících aktuálního roku (před naším měsícem)
    for (int m = 1; m < this->mesic; ++m) {
        celkemDni += pocetDniVMesici(m);
    }

    // Přičtení dnů v aktuálním měsíci
    celkemDni += this->den;

    return celkemDni;
}

// Vrátí číslo dne v týdnu
int datum::poradoveCisloDne() const {
    long long dny = pocetDniOdEpochy();


    return (dny + 2) % 7 + 1;
}

// Vypíše datum do konzole
ostream &operator<<(ostream &os, const datum &dat) {
    os << dat.getDatum() << ", pocet dni od 1. 1. 1970 je " << dat.pocetDniOdEpochy() << ", den v tydnu je "
       << dat.poradoveCisloDne() << "." << endl;
    return os;
}

// Destruktor
datum::~datum() = default;