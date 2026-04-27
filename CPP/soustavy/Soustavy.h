#ifndef SOUSTAVY_H
#define SOUSTAVY_H

#include <ostream>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

class Soustavy {
private:
    // Meze
    static const int MIN = 2;
    static const int MAX = 16;

    // Datové položky
    unsigned int desitkove;

    // Soukromé metody
    bool jePlatnaSoustava(int soustava) const;
    bool jePlatneCislo(string cislo, int soustava) const;
    int naDesitkovou(string cislo, int soustava);
    string naJinou(unsigned int cislo, int soustava) const;

public:
    // Konstruktory
    Soustavy();
    Soustavy(string cislo, int soustava);
    Soustavy(const Soustavy &soustavy);
    ~Soustavy();

    // Veřejné metody
    string vratCislo(int soustava) const;
    bool nastavCislo(string cislo, int soustava);

    // Výpis do konzole
    friend ostream& operator<<(ostream &os, const Soustavy &soustavy);
};


#endif
