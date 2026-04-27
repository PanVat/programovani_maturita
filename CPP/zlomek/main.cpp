#include "zlomek.h"
#include <cstring>
#include <iostream>
#include <limits>

using std::cout;
using std::cin;
using std::endl;

void vypis(zlomek &z, const char *text) {
    cout << text << endl;
    for (int i = 0; i < strlen(text); i++) {
        cout << "-";
    }
    cout << endl;
    cout << z << "; desetinne cislo: " << z.desetinne() << "; prevraceny zlomek: ";
    z.prevraceni();
    cout << z << "; kraceni: ";
    if (z.kraceni()) {
        cout  << z << endl;
    } else {
        cout << "Zlomek je v zakladnim tvaru." << endl;
    }
    cout << endl;
    return;
}

int zadani(std::string text) {
    int cislo;
    cout << "Zadej " << text << ":";
    cin >> cislo;
    while (cin.fail() || cin.peek() != '\n') {
        cout << "Nebylo zadano cele cislo." << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Zadej " << text << ":";
        cin >> cislo;
    }
    return cislo;
}

void nastavHodnotyZlomku(zlomek &z) {
    int citatel = zadani("citatele");
    int jmenovatel = zadani("jmenovatele");
    if (z.setZlomek(citatel, jmenovatel)) {
        vypis(z, "Objekt po zmene");
    } else {
        cout << "Jmenovatel nemuze byt nula." << endl;
    }
}

bool ukonci() {
    char klavesa;
    cout << "Klavesou \'k\' bude zadavani ukonceno: ";
    cin >> klavesa;
    if (klavesa == 'k') {
        return true;
    } else {
        return false;
    }
}

int main(int argc, char **argv) {
    zlomek z1;
    zlomek z2(1, 2);
    zlomek z3(z2);
    vypis(z1, "Objekt z1 vytvoreny vychozim konstruktorem");
    vypis(z2, "Objekt z2 vytvoreny konstruktorem s parametry");
    vypis(z3, "Objekt z3 vytvoreny kopirovacim konstruktorem z objektu z2");
    do {
        nastavHodnotyZlomku(z1);
        cout << endl;
    } while (!ukonci());
    return 0;
}

