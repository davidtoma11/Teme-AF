#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

ifstream f("apm2.in");
ofstream g("apm2.out");

long long n, m, q, tata[20005], cost_min;

struct Muchie {
    int x, y, c;
} muchie[100005];

vector<Muchie> apm;

// Funcție de sortare a muchiilor în funcție de cost
bool sortare(Muchie x, Muchie y) {
    return x.c < y.c;
}

// Funcție care întoarce rădăcina unei componente conexe
int radacina(int x) {
    if (tata[x] == x)
        return x;
    tata[x] = radacina(tata[x]);
    return tata[x];
}

// Funcție pentru unirea a două componente conexe
void unesc(int x, int y) {
    tata[radacina(x)] = radacina(y);
}

int main() {
    f >> n >> m >> q;

    // Inițializare tata pentru fiecare nod ca pe el însuși
    for (long long i = 1; i <= n; i++)
        tata[i] = i;

    // Citirea muchiilor
    for (int i = 1; i <= m; i++)
        f >> muchie[i].x >> muchie[i].y >> muchie[i].c;

    // Sortarea muchiilor în funcție de cost
    sort(muchie + 1, muchie + m + 1, sortare);

    // Aflarea costului minim folosind algoritmul lui Kruskal
    for (int i = 1; i <= m; i++) {
        if (radacina(muchie[i].x) != radacina(muchie[i].y)) {
            unesc(muchie[i].x, muchie[i].y);
            cost_min += muchie[i].c;
            apm.push_back(muchie[i]); // Construim primul APM
        }
    }

    // Citirea drumurilor speciale și calculul costului minim modificat
    while (q) {
        long long x, y, cost_min2 = 0;
        f >> x >> y;

        // Resetarea tatălui pentru fiecare nod
        for (long long i = 1; i <= n; i++)
            tata[i] = i;

        // Unirea drumurilor speciale
        unesc(x, y);

        // Refacerea algoritmului lui Kruskal pentru costul minim modificat
        for (int i = 0; i < apm.size(); i++)
            if (radacina(apm[i].x) != radacina(apm[i].y)) {
                unesc(apm[i].x, apm[i].y);
                cost_min2 += apm[i].c;
            }

        // Afișarea costului maxim nou pentru drumul special
        g << cost_min - cost_min2 - 1 << "\n";
        q--;
    }

    return 0;
}
