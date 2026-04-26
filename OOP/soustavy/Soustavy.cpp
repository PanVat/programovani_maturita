#include "Soustavy.h"

// Platné cifry
string platneCifry = "0123456789ABCDEF";

// Zjistí, jestli je zadaná číselná soustava platná
bool Soustavy::jePlatnaSoustava(int soustava) const {
    return (soustava >= MIN && soustava <= MAX);
}

// Výchozí konstruktor
Soustavy::Soustavy() {
    this->desitkove = 0;
}

// Parametrický konstruktor
Soustavy::Soustavy(string cislo, int soustava) : desitkove(0) {
    nastavCislo(cislo, soustava);
}

// Kopírovací konstruktor
Soustavy::Soustavy(const Soustavy &soustavy) {
    this->desitkove = soustavy.desitkove;
}

// Zjistí, jestli je číslo platné v zadané soustavě
bool Soustavy::jePlatneCislo(string cislo, int soustava) const {
    if (!jePlatnaSoustava(soustava)) {
        return false;
    }

    for (int i = 0; i < cislo.length(); ++i) {
        int nalezeno = platneCifry.find(cislo[i]);

        if (nalezeno == string::npos || nalezeno >= soustava) {
            return false;
        }
    }
    return true;
}

// Převede číslo z desítkové soustavy na jinou soustavu
string Soustavy::naJinou(unsigned int cislo, int soustava) const {
    if (cislo == 0) {
        return "0";
    }

    string vysledek = "";

    while (cislo > 0) {
        vysledek += platneCifry[cislo % soustava];
        cislo /= soustava;
    }

    reverse(vysledek.begin(), vysledek.end());

    return vysledek;
}

// Vrátí číslo v zadané soustavě
string Soustavy::vratCislo(int soustava) const {
    return naJinou(desitkove, soustava);
}

// Vrátí číslo v zadané soustavě v soustavě desítkové
int Soustavy::naDesitkovou(string cislo, int soustava) {
    unsigned int des = 0;

    for (int i = 0; i < cislo.length(); ++i) {
        int hodnota = platneCifry.find(cislo[i]);
        des += hodnota * pow(soustava, cislo.length() - i - 1);
    }
    return des;
}

// Nastaví číslo a soustavu
bool Soustavy::nastavCislo(string cislo, int soustava) {
    if (jePlatneCislo(cislo, soustava)) {
        this->desitkove = naDesitkovou(cislo, soustava);
        return true;
    }
    return false;
}

// Desktruktor
Soustavy::~Soustavy() = default;

// Výpis čísel do konzole
ostream &operator<<(ostream &os, const Soustavy &soustavy) {
    os << "Cislo v dvojkove soustave:" << soustavy.vratCislo(2) << endl;
    os << "Cislo v desitkove soustave:" << soustavy.vratCislo(10) << endl;
    os << "Cislo v sestnactkove soustave:" << soustavy.vratCislo(16) << endl;
    os << "Cislo v osmickove soustave:" << soustavy.vratCislo(8) << endl;
    return os;
}