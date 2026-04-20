#include "Zlomek.h"
#include <numeric> // Pro funkci gcd()

// Vymění čitatele a jmenovatele
void Zlomek::vymen(int &x, int &y) {
    int z = x;
    x = y;
    y = z;
}

// Výchozí konstruktor
Zlomek::Zlomek() {
    this->citatel = 1;
    this->jmenovatel = 1;
}

// Parametrický konstruktor
Zlomek::Zlomek(int citatel, int jmenovatel) {
    if (!nastavZlomek(citatel, jmenovatel)) {
        nastavZlomek(1, 1);
    }
    zkratZlomek();
}

// Kopírovací konstruktor
Zlomek::Zlomek(const Zlomek &zlomek) {
    this->citatel = zlomek.citatel;
    this->jmenovatel = zlomek.jmenovatel;
}

// Konstruktor
Zlomek::~Zlomek() = default;

// Vrátí čitatele
int Zlomek::vratCitatele() const {
    return this->citatel;
}

// Vrátí jmenovatele
int Zlomek::vratJmenovatele() const {
    return this->jmenovatel;
}

// Nastaví čitatele
void Zlomek::nastavCitatele(int citatel) {
    this->citatel = citatel;
}

// Nastaví jmenovatele, pokud je platný
bool Zlomek::nastavJmenovatele(int jmenovatel) {
    if (jmenovatel == 0) {
        return false;
    }
    this->jmenovatel = jmenovatel;
    return true;
}

// Nastaví celý zlomek, jestli je jmenovatel platný
bool Zlomek::nastavZlomek(int citatel, int jmenovatel) {
    if (nastavJmenovatele(jmenovatel)) {
        nastavCitatele(citatel);
        zkratZlomek();
        return true;
    }
    return false;
}

// Zkrátí zlomek
void Zlomek::zkratZlomek() {
    if (jmenovatel == 0) {
        return;
    }

    int delitel = gcd(citatel, jmenovatel);
    this->citatel /= delitel;
    this->jmenovatel /= delitel;

    if (jmenovatel < 0) {
        citatel = -citatel;
        jmenovatel = -jmenovatel;
    }
}

// Vrátí zlomek jako desetinné číslo
double Zlomek::naDesetinne() const {
    return (double) this->citatel / (double) this->jmenovatel;
}

// Zamění čitatele se jmenovatelem
bool Zlomek::prevratZlomek() {
    if (citatel == 0) {
        return false;
    }
    vymen(citatel, jmenovatel);
    return true;
}

// Operátor přiřazení
Zlomek &Zlomek::operator=(const Zlomek &zlomek) {
    if (this != &zlomek) {
        this->citatel = zlomek.citatel;
        this->jmenovatel = zlomek.jmenovatel;
    }
    return *this;
}

// Operátor sečtení zlomků
Zlomek Zlomek::operator+(const Zlomek &zlomek) {
    int novyCitatel = (this->citatel * zlomek.jmenovatel) + (zlomek.citatel * this->jmenovatel);
    int novyJmenovatel = (this->jmenovatel * zlomek.jmenovatel);

    Zlomek vysledek(novyCitatel, novyJmenovatel);

    vysledek.zkratZlomek();

    return vysledek;
}

// Vrátí zlomek v řetězcové podobě
string Zlomek::vratZlomek() const {
    if (citatel == 0) {
        return "0";
    }
    if (jmenovatel == 1) {
        return to_string(citatel);
    }
    return to_string(citatel) + "/" + to_string(jmenovatel);
}

// Výpis zlomku do konzole
ostream &operator<<(ostream &os, const Zlomek &zlomek) {
    os << zlomek.vratZlomek();
    return os;
}

