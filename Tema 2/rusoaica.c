#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define MAX_NODES 100000
#define MAX_EDGES 400000

using namespace std;

ifstream input("rusuoaica.in");
ofstream output("rusuoaica.out");

struct Edge {
    int from, to, cost;
} edges[MAX_EDGES + 5];

int n, m, threshold, result, parent[MAX_NODES + 5], componentSize[MAX_NODES + 5], x, y;

// Funcție pentru a compara muchiile în funcție de cost
bool compareEdges(Edge a, Edge b) {
    return (a.cost < b.cost);
}

// Funcție pentru găsirea părintelui unui nod într-un arbore de părinți (cu compresie de cale)
int findParent(int node) {
    if (parent[node] != node) {
        parent[node] = findParent(parent[node]);
    }
    return parent[node];
}

int main() {
    input >> n >> m >> threshold;

    for (int i = 1; i <= m; i++) {
        input >> edges[i].from >> edges[i].to >> edges[i].cost;
    }

    // Sortarea muchiilor în ordine crescătoare a costurilor
    sort(edges + 1, edges + m + 1, compareEdges);

    // Eliminarea muchiilor care au costul mai mare decât pragul
    while (m && edges[m].cost > threshold) {
        result -= edges[m].cost;
        m--;
    }

    // Inițializarea părinților și a dimensiunilor componentelor
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        componentSize[i] = 1;
    }

    // Aplicarea algoritmului lui Kruskal pentru a determina arborele de acoperire minimă
    for (int i = 1; i <= m; i++) {
        x = edges[i].from;
        y = edges[i].to;

        parent[x] = findParent(x);
        parent[y] = findParent(y);

        if (parent[x] != parent[y]) {
            // Adăugarea costului muchiei în rezultat
            result += edges[i].cost;

            // Unirea celor două componente conexe
            if (componentSize[parent[x]] < componentSize[parent[y]]) {
                componentSize[parent[y]] += componentSize[parent[x]];
                parent[parent[x]] = parent[y];
            } else {
                componentSize[parent[x]] += componentSize[parent[y]];
                parent[parent[y]] = parent[x];
            }
        } else {
            // Eliminarea costului muchiei în cazul formării unui ciclu
            result -= edges[i].cost;
        }
    }

    // Adăugarea costului minim pentru fiecare componentă conexă separată
    for (int i = 1; i <= n; i++) {
        if (parent[i] == i) {
            result += threshold;
        }
    }

    // Eliminarea costului adăugat pentru prima componentă conexă separată
    result -= threshold;

    output << result;

    return 0;
}
