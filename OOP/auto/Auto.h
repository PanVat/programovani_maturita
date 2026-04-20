#ifndef AUTO_H
#define AUTO_H

#include <string>
#include <ostream>

using namespace std;

class Auto {

private:
    // Datové položky
    string spz;
    double spotreba;
    int najeteKilometry;
    int rokVyroby;

    // Soukromé metody
    bool jePlatnaSPZ(string spz) const;
    int aktualniRok() const;

public:
    // Konstruktory
    Auto();
    Auto(const string &spz, double spotreba, int rokVyroby, int najeteKilometry);
    Auto(const Auto &vozidlo);
    ~Auto();

    // Gettery
    string vratSPZ() const;
    double vratSpotrebu() const;
    int vratNajeteKm() const;
    int vratRokVyroby() const;

    // Settery
    bool nastavSPZ(string spz);
    bool nastavSpotrebu(double spotreba);
    bool nastavKilometry(int najeteKilometry);
    bool nastavRokVyroby(int rokVyroby);

    // Veřejné metody
    int stariAuta() const;
    double prumerneNajeteKm() const;

    // Přetížený operátor výpisu
    friend ostream &operator<<(ostream &os, const Auto &vozidlo);
};


#endif
