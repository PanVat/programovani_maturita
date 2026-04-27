#ifndef RODNECISLO_H
#define RODNECISLO_H

#include <string>
#include <iostream>

using namespace std;

class rodneCislo {
private:
    // Datové položky
    string rc;

    // Metody
    bool jePlatneRC(string rc);
    string datumNarozeni() const;
public:
    // Konstruktory
    rodneCislo();
    rodneCislo(string rc);
    rodneCislo(const rodneCislo& rc);
    ~rodneCislo();

    // Gettery a settery
    string getRC() const;
    bool setRC(string rc);

    // Metody
    bool jeZena() const;
    int vek() const;

    // Výpis
    friend ostream& operator<<(ostream &os, const rodneCislo& rc);
};


#endif
