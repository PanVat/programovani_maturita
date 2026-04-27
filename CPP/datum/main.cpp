#include <iostream>
#include <limits>
#include "datum.h"

using std::endl;
using std::cout;
using std::cin;

bool konec() {
    char znak;
    cout << "Pro ukonceni stiskni klavesu \'k\'";
    cin >> znak;
    if (cin.fail() || cin.peek() != '\n') {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    } else if (znak == 'k') {
        return true;
    } else {
        return false;
    }
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

void vypisObjektu(const datum &r, std::string text) {
    cout << text << endl;
    for (int i = 0; i < text.length(); ++i) {
        cout << "-";
    }
    cout << endl;
    cout << r << endl;
}

int main() {
    datum d1;
    datum d2(1, 4, 2003);
    datum d3(d2);
    int den, mesic, rok;
    vypisObjektu(d1, "Objekt vytvoreny vychozim konstruktorem");
    vypisObjektu(d2, "Objekt vytvoreny konstruktorem s parametrem");
    vypisObjektu(d3, "Objekt vytvoreny kopirovacim konstruktorem");
    do {
        den = zadani("den");
        mesic = zadani("mesic");
        rok = zadani("rok");
        if (d1.setDatum(den, mesic, rok)){
            vypisObjektu(d1, "Objekt po zmene");
        }
        else {
            cout << "Chybne datum." << endl;
        }
    } while (!konec());
    return 0;
}


