#include <iostream>
#include "Auto.h"

int main() {
    // Deklarace objektů
    Auto a1;
    Auto a2("4T16404", 6.5, 2005, 192536);
    string spz;

    // Výpisy
    cout << "Objekt vytvoren konstruktorem bez parametru" << endl;
    cout << "-------------------------------------------" << endl;
    cout << a1;

    cout << endl;

    cout << "Objekt vytvoren konstruktorem s parametrem" << endl;
    cout << "------------------------------------------" << endl;
    cout << a2;

    cout << endl;

    cout << "Uzivatelske vstupy" << endl;
    cout << "------------------" << endl;

    // Zadání uživatelského vstupu
    bool opakovat;
    do {
        opakovat = false;
        cout << "Zadej SPZ auta:";
        getline(cin, spz);

        if (!a2.nastavSPZ(spz)) {
            cout << "Chybna SPZ." << endl;
            opakovat = true;
        }
    } while (opakovat);

    // Výpis objektu se změněnou SPZ
    cout << "Objekt 'a2' po zmene" << endl;
    cout << "--------------------" << endl;
    cout << a2;

    return 0;
}
