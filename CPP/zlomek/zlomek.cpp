#include "zlomek.h"

// Výchozí konstruktor
zlomek::zlomek() {
    this->citatel = 1;
    this->jmenovatel = 1;
}

// Parametrický konstruktor
zlomek::zlomek(int citatel, int jmenovatel) : zlomek() {
    if (setZlomek(citatel, jmenovatel)) {
        kraceni();
    }
}

// Kopírovací konstruktor
zlomek::zlomek(const zlomek &z) {
    this->citatel = z.citatel;
    this->jmenovatel = z.jmenovatel;
}

// Vrátí čitatele
int zlomek::getCitatel() const {
    return this->citatel;
}

// Vrátí jmenovatele
int zlomek::getJmenovatel() const {
    return this->jmenovatel;
}

// Vrátí zlomek
string zlomek::getZlomek() const {
    if (citatel == 0) return "0";

    string znamenko;
    int citatelPuvodni = citatel;
    int jmenovatelPuvodni = jmenovatel;

    if (citatelPuvodni < 0 ^ jmenovatelPuvodni < 0) {
        znamenko = "-";
    } else {
        znamenko = "";
    }

    return znamenko + to_string(abs(citatelPuvodni)) + "/" + to_string(abs(jmenovatelPuvodni));
}

// Zkrátí zlomek, pokud je to možné
bool zlomek::kraceni() {
    int citatelPuvodni = citatel;
    int jmenovatelPuvodni = jmenovatel;

    int delitel = nsd(citatel, jmenovatel);

    citatel /= delitel;
    jmenovatel /= delitel;

    if (citatel == citatelPuvodni && jmenovatel == jmenovatelPuvodni) {
        return false;
    }
    return true;
}

// Vrátí největšího společného dělitele
int zlomek::nsd(int citatel, int jmenovatel) const {
    return gcd(citatel, jmenovatel);
}

// Vymění parametry
void zlomek::vymena(int &x, int &y) {
    int z = x;
    x = y;
    y = z;
}

// Převrátí zlomek
bool zlomek::prevraceni() {
    if (citatel == 0) return false;
    vymena(citatel, jmenovatel);
    return true;
}

// Vrátí zlomek jako desetinné číslo
double zlomek::desetinne() const {
    return (double) this->citatel / this->jmenovatel;
}

// Nastaví zlomek
bool zlomek::setZlomek(int citatel, int jmenovatel) {
    if (jmenovatel == 0) return false;

    this->citatel = citatel;
    this->jmenovatel = jmenovatel;

    return true;
}

// Vypíše zlomek do konzole
ostream &operator<<(ostream &os, const zlomek &z) {
    os << z.getZlomek();
    return os;
}

// Destruktor
zlomek::~zlomek() = default;
