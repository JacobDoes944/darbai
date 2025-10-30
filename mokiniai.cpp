#include <iostream>
#include <string>
using namespace std;

const int maxmok = 3;
const int maxpaz = 3;

string bruh[maxmok];
int pazymiai[maxmok][maxpaz];
int kiek = 0;

void ivestis() {
    cout << "Iveskite mokinius (baigti - 'ne'):\n";
    while (kiek < maxmok) {
        cout << "Mokinio vardas: ";
        string vardas;
        cin >> vardas;
        if (vardas == "ne") break;

        bruh[kiek] = vardas;

        cout << "Kiek pazymiu (1-" << maxpaz << "): ";
        int kiek1;
        cin >> kiek1;


        for (int j = 0; j < maxpaz; j++) pazymiai[kiek][j] = 0;

        for (int j = 0; j < kiek1; j++) {
            cout << "Pazymys #" << j + 1 << ": ";
            cin >> pazymiai[kiek][j];
        }

        kiek++;
    }
}

void rasymas() {
    if (kiek == 0) {
        cout << "Nera mokiniu.\n";
        return;
    }
    for (int i = 0; i < kiek; i++) {
        cout << i + 1 << ". " << bruh[i] << ": ";
        bool turi = false;
        for (int j = 0; j < maxpaz; j++) {
            if (pazymiai[i][j] != 0) {
                cout << pazymiai[i][j] << " ";
                turi = true;
            }
        }
        if (!turi) cout << "(nera pazymiu)";
        cout << endl;
    }
}

void atnaujinti() {
    if (kiek == 0) {
        cout << "Nera mokiniu.\n";
        return;
    }

    cout << "Iveskite mokinio ID (1-" << kiek << "): ";
    int id;
    cin >> id;
    if (id < 1 || id > kiek) {
        cout << "Neteisingas ID.\n";
        return;
    }
    id--;

    cout << bruh[id] << " pazymiai: ";
    for (int j = 0; j < maxpaz; j++) {
        if (pazymiai[id][j] != 0)
            cout << j + 1 << ":" << pazymiai[id][j] << " ";
    }
    cout << endl;

    cout << "Kuri pazymi keisti? ";
    int nr;
    cin >> nr;
    if (nr < 1 || nr > maxpaz || pazymiai[id][nr - 1] == 0) {
        cout << "Neteisingas pazymio numeris.\n";
        return;
    }

    cout << "Naujas pazymys: ";
    cin >> pazymiai[id][nr - 1];
    cout << "Pazymys atnaujintas!\n";
}

void pasalinti() {
    if (kiek == 0) {
        cout << "Nera mokiniu.\n";
        return;
    }

    cout << "Iveskite mokinio ID, kuri norite pasalinti: ";
    int id;
    cin >> id;
    if (id < 1 || id > kiek) {
        cout << "Neteisingas ID.\n";
        return;
    }
    id--;

    cout << "Mokinys " << bruh[id] << " pasalintas.\n";

    for (int i = id; i < kiek - 1; i++) {
        bruh[i] = bruh[i + 1];
        for (int j = 0; j < maxpaz; j++) {
            pazymiai[i][j] = pazymiai[i + 1][j];
        }
    }


    bruh[kiek - 1].clear();
    for (int j = 0; j < maxpaz; j++) pazymiai[kiek - 1][j] = 0;

    kiek--;
}

int main() {
    int pasirinkimas;

    do {
        cout << "1. Ivesti mokinius ir ju pazymius\n";
        cout << "2. Perziureti visu mokiniu pazymius\n";
        cout << "3. Atnaujinti pazymi\n";
        cout << "4. Pasalinti mokini\n";
        cout << "0. Baigti programa\n";
        cout << "Pasirinkite: ";
        cin >> pasirinkimas;

        switch (pasirinkimas) {
            case 1: ivestis(); break;
            case 2: rasymas(); break;
            case 3: atnaujinti(); break;
            case 4: pasalinti(); break;
            case 0: cout << "Programa baigiama.\n"; break;
            default: cout << "Neteisingas pasirinkimas.\n";
        }
    } while (pasirinkimas != 0);

    return 0;
}
