#ifndef RETEZEC_H
#define RETEZEC_H

#include <ostream>
#include <cstddef>

using namespace std;

class Retezec {
private:
    // Datové položky
    char *retezec;
    size_t velikost;

public:
    // Konstruktory
    Retezec();
    Retezec(const char *retezec);
    Retezec(const Retezec &retezec);
    ~Retezec();

    // Vrátí délku řetězce
    size_t delka() const;

    // Přetížení operátorů indexů
    char &operator[](size_t index);
    const char &operator[](size_t index) const;

    // Přetížení aritmetických operátorů
    Retezec &operator=(const Retezec &retezec);
    Retezec &operator+=(const Retezec &retezec);
    Retezec operator+(const Retezec &retezec);

    // Výpis řetězce do konzole
    friend ostream &operator<<(ostream &os, const Retezec &retezec);
};


#endif
