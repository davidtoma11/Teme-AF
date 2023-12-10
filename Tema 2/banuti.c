#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

ifstream fin("banuti.in");
ofstream fout("banuti.out");

const long long INF = 1e18; // Valoare mare pentru a reprezenta infinitul
long long minrest[5005]; // Vector pentru a stoca costurile minime
int v[50005]; // Vectorul de monede
bool viz[5005]; // Vector pentru a tine evidenta nodurilor vizitate

// Structura pentru a reprezenta un nod in coada de prioritati
struct Element
{
    int node, cost;
    bool operator<(const Element &other) const
    {
        return cost > other.cost;
    }
};

// Functie pentru aplicarea algoritmului Dijkstra
void dijkstra()
{
    priority_queue<Element> pq;
    // Initializam coada de prioritati cu nodurile initiale
    for (int i = 0; i < v[1]; i++)
        if (minrest[i] != INF)
            pq.push({i, minrest[i]});

    while (!pq.empty())
    {
        int node = pq.top().node;
        pq.pop();

        // Daca nodul nu a fost vizitat inca, il vizitam si actualizam costurile
        if (viz[node] == 0)
        {
            viz[node] = true;
            for (int i = 1; i < v[1]; i++)
                if (minrest[i] != INF)
                {
                    int new_rest = node + i;
                    if (new_rest >= v[1])
                        new_rest -= v[1];

                    // Daca gasim o ruta mai buna, actualizam costul si adaugam in coada
                    if (minrest[new_rest] > minrest[node] + minrest[i])
                    {
                        minrest[new_rest] = minrest[node] + minrest[i];
                        pq.push({new_rest, minrest[new_rest]});
                    }
                }
        }
    }
}

int main()
{
    int n;
    fin >> n;
    for (int i = 1; i <= n; i++)
        fin >> v[i];

    sort(v + 1, v + n + 1);

    // Initializam costurile minime cu infinit
    for (int i = 0; i < v[1]; i++)
        minrest[i] = INF;

    // Pentru fiecare moneda, actualizam costurile minime
    for (int i = 1; i <= n; i++)
        minrest[v[i] % v[1]] = min(minrest[v[i] % v[1]], 1ll * v[i]);

    // Aplicam algoritmul lui Dijkstra pentru a gasi costurile minime
    dijkstra();

    long long ans = 0, ok = 1;

    // Calculam costul final
    for (int i = 0; i < v[1] && ok == 1; i++)
    {
        if (minrest[i] == INF)
        {
            ok = 0;
        }
        else
            ans = max(ans, minrest[i]);
    }

    // Afisam rezultatul
    if (ok == 0)
        fout << -1;
    else
        fout << ans - v[1];

    return 0;
}
