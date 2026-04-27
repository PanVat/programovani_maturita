#include <iostream>
#include "Soustavy.h"

using namespace std;

// Vypíše objekt a čáru dlouhou podle zadání
void vypisObjektu(const Soustavy &p, string text) {
    cout << text << endl;
    for (int i = 0; i < text.length(); i++) {
        cout << "-";
    }

    cout << endl;
    cout << p << endl;
    return;
}

int main() {
    Soustavy p1;
    Soustavy p2("1101", 2);
    Soustavy p3("ABCD", 16);
    Soustavy p4(p3);

    vypisObjektu(p1, "Objekt vytvoreny vychozim konstruktorem");
    vypisObjektu(p2, "Objekt vytvoreny konstruktorem s parametrem");
    vypisObjektu(p3, "Objekt vytvoreny konstruktorem s parametrem");
    vypisObjektu(p4, "Objekt vytvoreny kopirovacim konstruktorem");
    return 0;
}
