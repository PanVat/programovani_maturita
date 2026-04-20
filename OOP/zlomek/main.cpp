#include <iostream>
#include <limits>
#include "Zlomek.h"

// DRŽTE HUBY! //
using namespace std;

int nactiCislo(const string &vyzva) {
    int x;
    bool opakovat;

    do {
        cout << vyzva;
        cin >> x;
        opakovat = false;

        if (cin.fail()) {
            cout << "Zadejte prosim cele cislo." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opakovat = true;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (opakovat);
    return x;
}

int main() {
    Zlomek z1;
    Zlomek z2(3, 2);
    Zlomek z3(2, 6);
    Zlomek z4(0, 2);

    int citatel, jmenovatel;

    cout << "Objekt 'z1' vytvoreny konstruktorem bez parametru: " << z1 << ", " << z1.naDesetinne() << endl;
    cout << "Objekt 'z2' vytvoreny konstruktorem s parametry  : " << z2 << ", " << z2.naDesetinne() << endl;
    cout << "Objekt 'z3' vytvoreny konstruktorem s parametry  : " << z3 << ", " << z3.naDesetinne() << endl;
    cout << "Objekt 'z3' vytvoreny konstruktorem s parametry  : " << z4 << ", " << z4.naDesetinne() << endl << endl;

    z2.prevratZlomek();

    cout << "Objekt 'z2' po prevaceni  : " << z2 << endl;

    if (!z4.prevratZlomek()) {
        cout << "Zlomek 'z4' nelze prevratit." << endl;
    }

    cout << endl;

    cout << "Zmena zlomku 'z1'" << endl;
    cout << "-----------------" << endl;

    citatel = nactiCislo("Zadej citatele: ");
    jmenovatel = nactiCislo("Zadej jmenovatele: ");

    if (jmenovatel == 0) {
        cout << "Jmenovatel nemuze byt 0, nastavuji na 1." << endl;
        jmenovatel = 1;
    }

    z1.nastavJmenovatele(jmenovatel), z1.nastavCitatele(citatel);
    z1.zkratZlomek();

    cout << "Objekt 'z1' po zmene: " << z1 << endl << endl;

    z1.nastavCitatele(citatel);

    if (!z1.nastavJmenovatele(jmenovatel)) {
        cout << "Jmenovatel nemuze byt 0." << endl;
    }

    cout << "Scitani a prirazovani zlomku" << endl;
    cout << "----------------------------" << endl;

    z3 = z1 + z2;

    cout << "z3 = z1 + z2 = " << z1 << " + " << z2 << " = " << z3 << endl;
    return 0;
}
