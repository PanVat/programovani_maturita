#include "Auto.h"
#include <ctime>
#include <cctype>

using namespace std;

// Bezparametrický konstruktor
Auto::Auto() {
    this->spz = "NO_SPZ";
    this->spotreba = 0.1;
    this->rokVyroby = 1900;
    this->najeteKilometry = 0;
}

// Konstruktor s parametry - delegování konstruktoru (nastaví se hodnoty výchozího konstruktoru)
Auto::Auto(const string &spz, double spotreba, int rokVyroby, int najeteKilometry) : Auto() {
    nastavSPZ(spz);
    nastavSpotrebu(spotreba);
    nastavRokVyroby(rokVyroby);
    nastavKilometry(najeteKilometry);
}

// Kopírovací konstruktor
Auto::Auto(const Auto &vozidlo) {
    this->spz = vozidlo.spz;
    this->spotreba = vozidlo.spotreba;
    this->rokVyroby = vozidlo.rokVyroby;
    this->najeteKilometry = vozidlo.najeteKilometry;
}

// Vrátí SPZ
string Auto::vratSPZ() const {
    return this->spz;
}

// Vrátí spotřebu v litrech na 100 km
double Auto::vratSpotrebu() const {
    return this->spotreba;
}

// Vrátí počet najetých kilometrů
int Auto::vratNajeteKm() const {
    return this->najeteKilometry;
}

// Vrátí rok výroby vozidla
int Auto::vratRokVyroby() const {
    return this->rokVyroby;
}

// Nastaví SPZ z parametru, jestliže je platná
bool Auto::nastavSPZ(string spz) {
    if (jePlatnaSPZ(spz)) {
        this->spz = spz;
        return true;
    }
    return false;
}

// Nastaví spotřebu z parametru, jestliže je platná
bool Auto::nastavSpotrebu(double spotreba) {
    if (spotreba > 0) {
        this->spotreba = spotreba;
        return true;
    }
    return false;
}

// Nastaví počet najetých km z parametru
bool Auto::nastavKilometry(int najeteKilometry) {
    if (najeteKilometry >= 0) {
        this->najeteKilometry = najeteKilometry;
        return true;
    }
    return false;
}

// Nastaví rok výroby z parametru, jestliže je platný
bool Auto::nastavRokVyroby(int rokVyroby) {
    if (rokVyroby >= 1900 && rokVyroby <= aktualniRok()) {
        this->rokVyroby = rokVyroby;
        return true;
    }
    return false;
}

// Vrátí aktuální rok ze systémového data
int Auto::aktualniRok() const {
    time_t ted = time(nullptr);
    struct tm *t = localtime(&ted);

    return t->tm_year + 1900;
}

// Ověří platnost SPZ předané v parametru
bool Auto::jePlatnaSPZ(string spz) const {

    // Kontrola délky SPZ
    if (spz.length() < 5 || spz.length() > 7) {
        return false;
    }

    // Převod retězce na velká písmena
    for (char &c: spz) {
        c = (char) toupper(c);
    }

    // Jestli je první znak číslo, ale zároveň ne 0
    if (!isdigit(spz[0]) || spz[0] == '0') {
        return false;
    }

    // Jestli je druhý znak písmeno
    if (!isalpha(spz[1])) {
        return false;
    }

    // Vyloučení zakázaných znaků
    string zakazana = "GOQW";
    if (spz.find_first_of(zakazana) != string::npos) {
        return false; // Našli jsme zakázané písmeno -> neplatné
    }

    // Finální kontrola, jestli jsou zde pouze číslice a písmena
    for (char c: spz) {
        if (!isalnum(c))
            return false;
    }
    return true;
}

// Zjistí stáří auta a vrátí ho
int Auto::stariAuta() const {
    return aktualniRok() - this->rokVyroby;
}

// Vrátí průměrný počet najetých kilometrů za rok
double Auto::prumerneNajeteKm() const {
    return (double) this->najeteKilometry / (double) stariAuta();
}

// Operátor pro výpis do konzole
ostream &operator<<(ostream &os, const Auto &vozidlo) {
    os << fixed;
    os.precision(1);

    os << "SPZ                      " << vozidlo.vratSPZ() << endl;
    os << "Spotreba                 " << vozidlo.vratSpotrebu() << " litru na 100 km" << endl;
    os << "Rok vyroby               " << vozidlo.vratRokVyroby() << endl;
    os << "Stav tachometru          " << vozidlo.vratNajeteKm() << " km" << endl;
    os << "Stari vozu v letech      " << vozidlo.stariAuta() << endl;
    os << "Rocni prumer najetych km " << (int) vozidlo.prumerneNajeteKm() << " km" << endl;
    return os;
}

// Destruktor
Auto::~Auto() = default;

