#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>

#define DN 505

using namespace std;

vector<int> fol(DN, 0); // Vector pentru a marca nodurile care au fost folosite în cuplaj
vector<int> gr[DN]; // Listă de adiacență pentru graful bipartit
int n, m, st[DN], dr[DN]; // Vectorii pentru cuplaj și dimensiunile grafului

// Funcție pentru a incerca să faca un cuplaj începand cu un anumit nod
int cuplaj(int nod) {
    if (fol[nod])
        return 0;
    fol[nod] = 1;

    int i = 0;
    while (i < gr[nod].size()) {
        if (dr[gr[nod][i]] == 0 || cuplaj(dr[gr[nod][i]])) {
            st[nod] = gr[nod][i];
            dr[gr[nod][i]] = nod;
            return 1;
        }
        ++i;
    }

    return 0;
}

int main() {
    ifstream f("senat.in");
    ofstream g("senat.out");
    f >> n >> m;
    f.get(); // Consumăm newline-ul după citirea m
    string s;

    // Construim graful bipartit
    for (int i = 1; i <= m; ++i) {
        getline(f, s);
        int j = 0;
        while (j < s.size()) {
            if (isdigit(s[j])) {
                int nc = 0;
                while (isdigit(s[j])) {
                    nc = nc * 10 + s[j] - '0';
                    ++j;
                }
                gr[i].push_back(nc + n); // Adăugăm vecinii în graful bipartit
            }
            ++j;
        }
    }

    bool ok = true;

    // Algoritmul lui Hopcroft-Karp pentru gasirea cuplajului maxim
    while (ok) {
        ok = false;
        fill(fol.begin(), fol.end(), 0);

        // Incercăm să gasim un cuplaj incepand cu fiecare nod neasignat
        for (int i = 1; i <= m; ++i)
            if (st[i] == 0)
                if (cuplaj(i)) {
                    ok = true;
                }
    }

    // Verificam dacă s-a gasit un cuplaj perfect
    for (int i = 1; i <= m; ++i)
        if (st[i] == 0) {
            g << "0"; // inseamna că nu există cuplaj perfect
            return 0;
        }

    // Afisam rezultatul, reprezentând perechile de cuplaj
    for (int i = 1; i <= m; ++i)
        g << st[i] - n << '\n'; // Afisam rezultatul

    return 0;
}

