#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

struct menuItemType {
    string pavadinimas;
    double kaina;
};

int getData(menuItemType menuList[]);
void rodyti(menuItemType menuList[], int kiekis);
void spausdinti(menuItemType menuList[], int kiekis, int porcijos[]);



int getData(menuItemType menuList[]) {
    ifstream in;
    in.open("menu.txt");

    string pav;
    double kaina;
    int i = 0;

    while (!in.eof()) {
        in >> menuList[i].pavadinimas >> menuList[i].kaina;
        i++;
    }
    return i;
}

void rodyti(menuItemType menuList[], int kiekis) {
    cout << "Pusryciu meniu:\n";
    for (int i = 0; i < kiekis; i++) {
        cout << i + 1 << ". "
             << left << setw(40) << menuList[i].pavadinimas
             << fixed << setprecision(2) << menuList[i].kaina << "EUR" << endl;
    }
    cout << endl;
}

void spausdinti(menuItemType menuList[], int kiekis, int porcijos[]) {
    ofstream out("receipt.txt");

    double suma = 0;

    cout << "\n--- Jusu uzsakymas ---\n";
    out << "Jusu uzsakymas:\n\n";

    for (int i = 0; i < kiekis; i++) {
        if (porcijos[i] > 0) {
            double tarpine = porcijos[i] * menuList[i].kaina;
            suma += tarpine;

            cout << porcijos[i] << " x "
                 << left << setw(40) << menuList[i].pavadinimas
                 << fixed << setprecision(3) << tarpine << "EUR" << endl;

            out << porcijos[i] << " x "
                << left << setw(40) << menuList[i].pavadinimas
                << fixed << setprecision(3) << tarpine << "EUR" << endl;
        }
    }

    double pvm = suma * 0.21;
    double galutine = suma + pvm;

    cout << "\nPVM (21%): " << fixed << setprecision(2) << pvm << "EUR" << endl;
    cout << "Galutine suma: " << fixed << setprecision(2) << galutine << "EUR" << endl;

    out << "\nPVM (21%): " << fixed << setprecision(2) << pvm << "EUR" << endl;
    out << "Galutine suma: " << fixed << setprecision(2) << galutine << "EUR" << endl;

    out.close();
}
int main() {
    const int MAX = 50;
    menuItemType menuList[MAX];
    int porcijos[MAX] = {0};

    int meniuKiekis = getData(menuList);
    if (meniuKiekis == 0) {
        cout << "Klaida: nepavyko nuskaityti menu.txt failo!" << endl;
        return 1;
    }

    cout << "Sveiki atvyke i restorana!" << endl << endl;

    rodyti(menuList, meniuKiekis);

    int pasirinkimas, kiek;
    while (true) {
        cout << "iveskite patiekalo numeri (0 - baigti): ";
        cin >> pasirinkimas;

        if (pasirinkimas == 0) break;
        if (pasirinkimas < 1 || pasirinkimas > meniuKiekis) {
            cout << "Neteisingas pasirinkimas!" << endl;
            continue;
        }

        cout << "Kiek porciju norite?";
        cin >> kiek;

        if (kiek < 1) {
            cout << "Neteisingas kiekis!" << endl;
            continue;
        }

        porcijos[pasirinkimas - 1] += kiek;
    }

    spausdinti(menuList, meniuKiekis, porcijos);

    cout << "\nSaskaita issaugota faile receipt.txt" << endl;

    return 0;
}