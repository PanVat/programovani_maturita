#include <iostream>
#include <limits>
#include "rodneCislo.h"

using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::numeric_limits;
using std::streamsize;

bool konec() {
    char znak;
    cout << "Pro ukonceni stiskni klavesu \'k\'";
    cin >> znak;
    if (cin.fail() || cin.peek() != '\n') {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    } else if (znak == 'k') {
        return true;
    } else {
        return false;
    }
}

void vypisObjektu(const rodneCislo &r, std::string text) {
    cout << text << endl;
    for (int i = 0; i < text.length(); ++i) {
        cout << "-";
    }
    cout << endl;
    cout << r << endl;
}

int main() {
    rodneCislo rc1;
    rodneCislo rc2("5412310013");
    rodneCislo rc3(rc1);
    std::string rc;
    vypisObjektu(rc1,"Objekt vytvoreny vychozim konstruktorem");
    vypisObjektu(rc2,"Objekt vytvoreny konstruktorem s parametrem");
    vypisObjektu(rc3,"Objekt vytvoreny kopirovacim konstruktorem");

    do {
        cout << "Zadejte rodne cislo: ";
        getline(cin,rc);
        if (rc1.setRC(rc)) {
            vypisObjektu(rc1,"Objekt po zmene");
        } else {
            cout << "Chybne rodne cislo." << endl;
        }
    } while (!konec());

    return 0;
}
