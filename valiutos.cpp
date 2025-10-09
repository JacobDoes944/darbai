#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    const string valiutos[] = {"GBP", "USD", "INR"};
    const string valiutuPavadinimai[] = {
        "Didziosios Britanijos svaras",
        "JAV doleris",
        "Indijos rupija"
    };
    const string funkcijos[] = {"Nutraukti programa", "Palyginti", "Pirkti", "Parduoti"};

    double kursai[3][3] = {
        {0.8729, 1.7920, 104.6918},
        {0.8600, 1.1460, 101.3862},
        {0.9220, 1.0 / 1.2340, 1.0 / 107.8546}
    };

    cout << fixed << setprecision(2);

    bool veikia = true;
    while (veikia) {
        cout << "\nPasirinkite funkcija:\n";
        for (int i = 0; i < 4; i++)
            cout << i << ": " << funkcijos[i] << endl;

        int funkcija;
        cin >> funkcija;

        if (funkcija == 0) {
            cout << "Programa baigta.\n";
            veikia = false;
            continue;
        }

        cout << "\nPasirinkite valiuta:\n";
        for (int i = 0; i < 3; i++)
            cout << i + 1 << ": " << valiutos[i] << " - " << valiutuPavadinimai[i] << endl;

        int valiutosIndeksas;
        cin >> valiutosIndeksas;
        valiutosIndeksas--;

        double kursas = kursai[funkcija - 1][valiutosIndeksas];
        cout << "\n1 EUR = " << kursas << " " << valiutos[valiutosIndeksas] << endl;

        cout << "Iveskite kieki: ";
        double kiekis;
        cin >> kiekis;

        double rezultatas = kursas * kiekis;
        cout << kiekis << " EUR = " << rezultatas << " " << valiutos[valiutosIndeksas] << endl;
    }
    return 0;
}
