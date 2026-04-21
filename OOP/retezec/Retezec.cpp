#include "Retezec.h"

#include <cstring>

// Výchozí konstruktor
Retezec::Retezec() {
    this->retezec = new char[1];
    this->retezec[0] = '\0';
    this->velikost = 0;
}

// Parametrický konstruktor
Retezec::Retezec(const char *retezec) {
    if (retezec == nullptr) {
        Retezec();
    } else {
        this->velikost = strlen(retezec);
        this->retezec = new char[this->velikost + 1];
        strcpy(this->retezec, retezec);
    }
}

// Kopírovací konstruktor
Retezec::Retezec(const Retezec &retezec) {
    this->velikost = retezec.velikost;
    this->retezec = new char[this->velikost + 1];
    strcpy(this->retezec, retezec.retezec);
}

// Destruktor - uvoní paměť řetězce pomocí operátoru delete
Retezec::~Retezec() {
    delete [] this->retezec;
}

// Vrátí velikost řetězce
size_t Retezec::delka() const {
    return this->velikost;
}

// Přetížení operátoru pro přístup ke znaku pomocí indexu
char &Retezec::operator[](size_t index) {
    return this->retezec[index];
}

// Přetížení operátoru pro přístup ke znaku pomocí indexu (řetězec je konstanta)
const char &Retezec::operator[](size_t index) const {
    return this->retezec[index];
}

// Přiřazení řetězce do jiného řetězce
Retezec &Retezec::operator=(const Retezec &retezec) {
    if (this == &retezec) {
        return *this;
    }

    delete [] this->retezec;

    this->velikost = retezec.velikost;
    this->retezec = new char[this->velikost + 1];
    strcpy(this->retezec, retezec.retezec);

    return *this;
}

// Připojí jiný řetězec k řetězci
Retezec & Retezec::operator+=(const Retezec &retezec) {
    size_t novaVelikost = this->velikost + retezec.velikost;
    char *novaPamet = new char[novaVelikost + 1];

    strcpy(novaPamet, this->retezec);
    strcat(novaPamet, retezec.retezec);

    delete [] this->retezec;

    this->retezec = novaPamet;
    this->velikost = novaVelikost;

    return *this;
}

// Vrátí spojené řetězce
Retezec Retezec::operator+(const Retezec &retezec) {
    Retezec vysledek(*this);
    vysledek += retezec;
    return vysledek;
}

// Výpis řetězce do konzole
ostream & operator<<(ostream &os, const Retezec &retezec) {
    for (int i = 0; i < retezec.delka(); i++) {
        os << retezec[i];
    }
    return os;
}
