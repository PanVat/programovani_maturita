# Návod pro C++

---

### Výměna parametrů

```cpp
void Zlomek::vymen(int &x, int &y) {
    int z = x;
    x = y;
    y = z;
}
```

---

### Parametrický konstruktor

```
rodneCislo::rodneCislo(string rc) : rodneCislo() {
    if (!setRC(rc)) {
        cerr << "Chybne rodne cislo." << endl;
    }
}
```

---

### Kopírovací konstruktor

```
Zlomek::Zlomek(const Zlomek &zlomek) {
    this->citatel = zlomek.citatel;
    this->jmenovatel = zlomek.jmenovatel;
}
```

---

### Získání aktuálního data

```
time_t momentalne = time(nullptr);
struct tm *ted = localtime(&momentalne);

this->rok = ted->tm_year + 1900;
this->mesic = ted->tm_mon + 1;
this->den = ted->tm_mday;
```

---

### Operátor =

```
Zlomek &operator=(const Zlomek &zlomek);
```

```
Zlomek &Zlomek::operator=(const Zlomek &zlomek) {
    if (this != &zlomek) {
        this->citatel = zlomek.citatel;
        this->jmenovatel = zlomek.jmenovatel;
    }
    return *this;
}
```

---

### Operátor +
```
Zlomek operator+(const Zlomek &zlomek);
```
```
Zlomek Zlomek::operator+(const Zlomek &zlomek) {
    int novyCitatel = (this->citatel * zlomek.jmenovatel) + (zlomek.citatel * this->jmenovatel);
    int novyJmenovatel = (this->jmenovatel * zlomek.jmenovatel);

    Zlomek vysledek(novyCitatel, novyJmenovatel);

    vysledek.zkratZlomek();

    return vysledek;
}
```

---

### Operátor <<

```
friend ostream &operator<<(ostream &os, const Zlomek &zlomek);
```

```
ostream &operator<<(ostream &os, const Zlomek &zlomek) {
    os << zlomek.vratZlomek();
    return os;
}
```
