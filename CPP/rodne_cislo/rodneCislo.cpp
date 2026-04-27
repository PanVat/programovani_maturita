#include "rodneCislo.h"

// Výchozí konstruktor
rodneCislo::rodneCislo() {
    this->rc = "5451010015";
}

// Parametrický konstruktor
rodneCislo::rodneCislo(string rc) : rodneCislo() {
    if (!setRC(rc)) {
        cerr << "Chybne rodne cislo." << endl;
    }
}

// Kopírovací konstruktor
rodneCislo::rodneCislo(const rodneCislo &rc) {
    this->rc = rc.rc;
}

// Vrátí rodné číslo
string rodneCislo::getRC() const {
    return this->rc;
}

// Nastaví rodné číslo, jestliže je platné
bool rodneCislo::setRC(string rc) {
    if (jePlatneRC(rc)) {
        this->rc = rc;
        return true;
    }
    return false;
}

// Zjistí, jestli rodné číslo patří ženě, nebo muži
bool rodneCislo::jeZena() const {
    return stoi(rc.substr(2, 2)) > 50;
}

// Vrátí věk osoby
int rodneCislo::vek() const {
    time_t momentalne = time(nullptr);
    struct tm *ted = localtime(&momentalne);

    // Aktuální datum ze systémového času
    int aktualniRok = ted->tm_year + 1900;
    int aktualniMesic = ted->tm_mon + 1;
    int aktualniDen = ted->tm_mday;

    // Vyextrahované datum z rodného čísla
    int rr = stoi(rc.substr(0, 2));
    int mm = stoi(rc.substr(2, 2));
    int dd = stoi(rc.substr(4, 2));

    // Určení skutečného roku narození
    int rokNarozeni = (rr < 54) ? (2000 + rr) : (1900 + rr);

    // Očištění měsíce
    int mesicNarozeni = mm;

    if (mesicNarozeni > 70) mesicNarozeni -= 70;
    else if (mesicNarozeni > 50) mesicNarozeni -= 50;
    else if (mesicNarozeni > 20) mesicNarozeni -= 20;

    // Výpočet věku
    int vek = aktualniRok - rokNarozeni;

    // Kontrola, jestli už narozeniny proběhly
    if (aktualniMesic < mesicNarozeni || (aktualniMesic == mesicNarozeni && aktualniDen < dd)) {
        vek--;
    }

    return vek;
}

// Testování platnosti rodného čísla
bool rodneCislo::jePlatneRC(string rc) {
    // Rodné číslo nemá 10 cifer
    if (rc.length() != 10) {
        return false;
    }

    // Rodné číslo musí obsahovat pouze číslice
    if (rc.find_first_not_of("0123456789") != string::npos) {
        return false;
    }

    // Vezmeme prvních 9 číslic místo celého rodného čísla
    long long orezaneRC = stoll(rc.substr(0, 9));
    int zbytek = orezaneRC % 11;
    int desataCislice = rc[9] - '0';

    // Validace dělitelnosti 11
    if (zbytek == 10) {
        if (desataCislice != 0) return false;
    } else {
        if (desataCislice != zbytek) return false;
    }

    // Extrahování roku, měsíce a dne
    int rr = stoi(rc.substr(0, 2));
    int mm = stoi(rc.substr(2, 2));
    int dd = stoi(rc.substr(4, 2));

    // Dekódování měsíce a pohlaví
    int mesic = mm;
    if (mesic > 70) {
        mesic -= 70;
    } else if (mesic > 50) {
        mesic -= 50;
    } else if (mesic > 20) {
        mesic -= 20;
    }

    // Kontrola rozsahu měsíce a dne
    if (mesic < 1 || mesic > 12) return false;
    if (dd < 1 || dd > 31) return false;

    // Kontrola roku
    int rok = (rr < 54) ? (2000 + rr) : (1900 + rr);
    if (rok < 1954) return false;

    return true;
}

// Vrátí datum narození ve formátu dd. mm. RRRR
string rodneCislo::datumNarozeni() const {
    // Extrahování údajů
    int rr = stoi(rc.substr(0, 2));
    int mm = stoi(rc.substr(2, 2));
    int den = stoi(rc.substr(4, 2));

    // Očištění měsíce
    int mesic = mm;
    if (mesic > 70) mesic -= 70;
    else if (mesic > 50) mesic -= 50;
    else if (mesic > 20) mesic -= 20;

    // Dopočtení celého roku
    int rok = (rr < 54) ? (2000 + rr) : (1900 + rr);

    // Výsledný řetězec
    return to_string(den) + ". " + to_string(mesic) + ". " + to_string(rok);
}

// Výpis rodného čísla do konzole
ostream &operator<<(ostream &os, const rodneCislo &rc) {
    os << "Rodne cislo: " << rc.getRC() << endl;
    os << "Narozen: " << rc.datumNarozeni() << endl;
    os << "Pohlavi: " << (rc.jeZena() ? "zena" : "muz") << endl;
    os << "Vek: " << rc.vek() << endl;
    return os;
}

// Destruktor
rodneCislo::~rodneCislo() = default;
