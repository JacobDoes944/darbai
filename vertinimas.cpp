#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

const int K = 20;
const int MAX = 40;

struct Studentas {
    int id;
    string ats;
    int taskai;
    double proc;
    int pazymys;
};

int skaiciuokTaskus(const string& teisingi, const string& ats) {
    int t = 0;
    for (int i = 0; i < K; i++) {
        char a = toupper((unsigned char)ats[i]);
        char te = toupper((unsigned char)teisingi[i]);

        if (a == '-') {
            t += 0;
        } else if (a == te) {
            t += 2;
        } else {
            t -= 1;
        }
    }
    return t;
}
int pazymysIsProcentu(double p) {
    if (p >= 95) return 10;
    else if (p >= 85) return 9;
    else if (p >= 75) return 8;
    else if (p >= 65) return 7;
    else if (p >= 55) return 6;
    else if (p >= 50) return 5;
    else if (p >= 35) return 4;
    else if (p >= 25) return 3;
    else if (p >= 15) return 2;
    else return 1;
}

bool nuskaitykDuomenis(const string& failas, string& teisingi, vector<Studentas>& grupe) {
    ifstream in(failas);
    if (!in) return false;

    in >> teisingi; // pirma eilutė (20 T/F)
    if ((int)teisingi.size() != K) return false;

    Studentas s;
    while (in >> s.id >> s.ats) {
        if ((int)s.ats.size() != K) return false; // paprastai tikrinam
        grupe.push_back(s);
    }

    return true;
}
void apskaiciuokRezultatus(const string& teisingi, vector<Studentas>& grupe) {
    for (auto& s : grupe) {
        s.taskai = skaiciuokTaskus(teisingi, s.ats);

        s.proc = (s.taskai / 40.0) * 100.0;

        if (s.proc < 0) s.proc = 0;
        if (s.proc > 100) s.proc = 100;

        s.pazymys = pazymysIsProcentu(s.proc);
    }
}
void isveskRezultatus(const vector<Studentas>& grupe) {
    cout << "ID\tTaskai\tProcentai\tPazymys\n";
    cout << "----------------------------------------\n";
    cout << fixed << setprecision(2);
    for (const auto& s : grupe) {
        cout << s.id << "\t" << s.taskai << "\t" << s.proc << "%\t\t" << s.pazymys << "\n";
    }
}

void issaugokIFaila(const string& failas, const vector<Studentas>& grupe) {
    ofstream out(failas);
    out << "ID\tTaskai\tProcentai\tPazymys\n";
    out << fixed << setprecision(2);
    for (const auto& s : grupe) {
        out << s.id << "\t" << s.taskai << "\t" << s.proc << "\t" << s.pazymys << "\n";
    }
}

void klasesStatistika(const vector<Studentas>& grupe) {
    cout << "\n=== Klases statistika ===\n";
    int n = (int)grupe.size();
    cout << "Studentu skaicius: " << n << "\n";
    if (n == 0) return;

    int maxT = grupe[0].taskai, minT = grupe[0].taskai;
    double sumaT = 0, sumaP = 0;
    int pasisk[11] = {0}; // 1..10

    for (const auto& s : grupe) {
        if (s.taskai > maxT) maxT = s.taskai;
        if (s.taskai < minT) minT = s.taskai;
        sumaT += s.taskai;
        sumaP += s.proc;
        if (s.pazymys >= 1 && s.pazymys <= 10)
            pasisk[s.pazymys]++;

    }

    cout << fixed << setprecision(2);
    cout << "Didziausi taskai: " << maxT << "\n";
    cout << "Maziausi taskai: " << minT << "\n";
    cout << "Vidutiniai taskai: " << (sumaT / n) << "\n";
    cout << "Vidutinis procentas: " << (sumaP / n) << "%\n";

    cout << "\nPazymiu pasiskirstymas:\n";
    for (int g = 1; g <= 10; g++) {
        cout << g << ": " << pasisk[g] << "\n";
    }
}

void klausimuStatistika(const string& teisingi, const vector<Studentas>& grupe) {
    int n = (int)grupe.size();
    int teisingiK[K] = {0}, klaidingiK[K] = {0}, neatsK[K] = {0};

    for (const auto& s : grupe) {
        for (int i = 0; i < K; i++) {
            if (s.ats[i] == '-') neatsK[i]++;
            else if (s.ats[i] == teisingi[i]) teisingiK[i]++;
            else klaidingiK[i]++;
        }
    }

    cout << "\n=== Kiekvieno klausimo statistika ===\n";
    cout << "Nr\tTeisingi\tKlaidingi\tNeatsakyti\tTeisingu %\n";
    cout << fixed << setprecision(2);

    double minProc = 101.0;

    for (int i = 0; i < K; i++) {
        double p = (n == 0) ? 0.0 : (teisingiK[i] * 100.0 / n);
        cout << (i + 1) << "\t" << teisingiK[i]
             << "\t\t" << klaidingiK[i]
             << "\t\t" << neatsK[i]
             << "\t\t" << p << "%\n";
        if (p < minProc) minProc = p;
    }

    cout << "\nSunkiausias(-i) klausimas(-ai): ";
    for (int i = 0; i < K; i++) {
        double p = (n == 0) ? 0.0 : (teisingiK[i] * 100.0 / n);
        if (p == minProc) cout << (i + 1) << " ";
    }
    cout << "(teisingu % = " << minProc << "%)\n";
}

void paieskaPagalID(const vector<Studentas>& grupe) {
    cout << "\n=== Paieska pagal ID ===\n";
    int id;
    cout << "Ivesk ID (0 - baigti): ";
    while (cin >> id) {
        if (id == 0) break;

        bool rasta = false;
        for (const auto& s : grupe) {
            if (s.id == id) {
                cout << fixed << setprecision(2);
                cout << "Rasta: ID=" << s.id
                     << ", taskai=" << s.taskai
                     << ", procentai=" << s.proc << "%"
                     << ", pazymys=" << s.pazymys << "\n";
                rasta = true;
                break;
            }
        }
        if (!rasta) cout << "Studentas nerastas.\n";

        cout << "Ivesk ID (0 - baigti): ";
    }
}

int main() {
    string teisingi;
    vector<Studentas> grupe;

    if (!nuskaitykDuomenis("testData.txt", teisingi, grupe)) {
        cout << "Klaida: nepavyko nuskaityti testData.txt (patikrink formata).\n";
        return 1;
    }

    apskaiciuokRezultatus(teisingi, grupe);

    isveskRezultatus(grupe);
    issaugokIFaila("results.txt", grupe);
    cout << "\nRezultatai issaugoti faile results.txt\n";

    klasesStatistika(grupe);
    klausimuStatistika(teisingi, grupe);
    paieskaPagalID(grupe);

    return 0;
}
