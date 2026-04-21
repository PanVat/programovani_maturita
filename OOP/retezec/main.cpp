#include <iostream>
#include "Retezec.h"

using namespace std;

int main() {
    Retezec s0;
    Retezec s1("Texxxtt");
    Retezec s2("Stringggss");
    Retezec s3;
    Retezec s4(s1);

    cout << "Objekt vytvoreny vychozim konstruktorem" << endl;
    cout << "s0: " << s0 << endl;
    cout << "Objekty vytvorene konstruktorem s parametrem" << endl;
    cout << "s1: " << s1 << endl;
    cout << "s2: " << s2 << endl;
    cout << "Objekt vytvoreny kopirovacim konstruktorem" << endl;
    cout << "s4: " << s4 << endl;

    cout << endl;

    cout << "Prirazeni (s2 = s1):" << endl;
    s2 = s1;
    cout << "s1: " << s1 << endl;
    cout << "s2: " << s2 << endl;

    cout << endl;

    cout << "Secteni (s3 = s1 + s2):" << endl;
    s3 = s1 + s2;
    cout << "s1: " << s1 << endl;
    cout << "s2: " << s2 << endl;
    cout << "s3: " << s3 << endl;

    cout << endl;

    cout << "Secteni (s1 += s2 + s3):" << endl;
    s1 += s2 + s3;
    cout << "s1: " << s1 << endl;
    cout << "s2: " << s2 << endl;
    cout << "s3: " << s3 << endl;
    return 0;
}
