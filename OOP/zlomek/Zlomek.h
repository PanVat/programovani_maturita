#ifndef ZLOMEK_H
#define ZLOMEK_H

#include <string>
#include <ostream>

// DRŽTE HUBY! //
using namespace std;

class Zlomek {

private:
    int citatel;
    int jmenovatel;

    void vymen(int &x, int &y);

public:
    // Konstruktory
    Zlomek();
    Zlomek(int citatel, int jmenovatel);
    Zlomek(const Zlomek& zlomek);

    // Destruktor
    ~Zlomek();

    // Gettery
    int vratCitatele() const;
    int vratJmenovatele() const;
    string vratZlomek() const;

    // Settery
    void nastavCitatele(int citatel);
    bool nastavJmenovatele(int jmenovatel);
    bool nastavZlomek(int citatel, int jmenovatel);

    // Metody
    void zkratZlomek();
    double naDesetinne() const;
    bool prevratZlomek();

    // Přetížení operátorů
    Zlomek &operator=(const Zlomek &zlomek);
    Zlomek operator+(const Zlomek &zlomek);

    // Výpis objektu do konzole
    friend ostream &operator<<(ostream &os, const Zlomek &zlomek);
};

#endif
