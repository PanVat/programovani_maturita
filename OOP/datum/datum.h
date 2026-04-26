#ifndef DATUM_H
#define DATUM_H

#include <ostream>
#include <string>

using namespace std;

class datum {
private:
    // Konstanty
    static const int MIN_ROK = 1970;
    static const int MAX_ROK = 2100;

    // Datové položky
    int den;
    int mesic;
    int rok;

    // Metody
    bool jePrestupnyRok(int rok) const;
    int pocetDniVMesici(int mesic) const;
public:
    // Konstruktory
    datum();
    datum(int den, int mesic, int rok);
    datum(const datum& dat);
    ~datum();

    // Gettery
    int getDen() const;
    int getMesic() const;
    int getRok() const;
    string getDatum() const;

    // Settery
    bool setDatum(int den, int mesic, int rok);

    // Metody
    long long pocetDniOdEpochy() const;
    int poradoveCisloDne() const;

    // Výpis do konzole
    friend ostream& operator<<(ostream &os, const datum& dat);
};


#endif
