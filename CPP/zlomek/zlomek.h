#ifndef ZLOMEK_H
#define ZLOMEK_H

#include <ostream>
#include <string>
#include <numeric>
#include <cmath>

// Usingy
using std::to_string, std::gcd;
using std::string, std::ostream;
using std::endl;

class zlomek {
private:
    // Datové položky
    int citatel;
    int jmenovatel;

    // Metody
    int nsd(int citatel, int jmenovatel) const;
    void vymena(int &x, int &y);

public:
    // Konstruktory
    zlomek();
    zlomek(int citatel, int jmenovatel);
    zlomek(const zlomek& z);
    ~zlomek();

    // Gettery
    int getCitatel() const;
    int getJmenovatel() const;
    string getZlomek() const;

    // Settery
    bool setZlomek(int citatel, int jmenovatel);

    // Metody
    bool kraceni();
    bool prevraceni();
    double desetinne() const;

    // Výpis
    friend ostream &operator<<(ostream &os, const zlomek& z);
};


#endif
