#include <fstream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

const long long INF = 1e18;

int nrOrase, nodInceput, nodSfarsit;
vector<vector<int>> listaAdiacenta, capacitateReziduala;

void citire() {
    ifstream fin("harta.in");
    fin >> nrOrase;

    nodInceput = 0;
    nodSfarsit = 2 * nrOrase + 1;

    listaAdiacenta.resize(2 * nrOrase + 10);
    capacitateReziduala.resize(2 * nrOrase + 10, vector<int>(2 * nrOrase + 10));

    // Construim graful bipartit
    for (int i = 1; i <= nrOrase; i++)
        for (int j = 1; j <= nrOrase; j++)
            if (i != j) {
                listaAdiacenta[i].push_back(j + nrOrase);
                listaAdiacenta[j + nrOrase].push_back(i);
                capacitateReziduala[i][j + nrOrase] = 1;
            }

    int gradIntrare, gradIesire;
    for (int i = 1; i <= nrOrase; i++) {
        fin >> gradIntrare >> gradIesire;

        // Adăugam muchiile în graf
        listaAdiacenta[nodInceput].push_back(i);
        listaAdiacenta[i].push_back(nodInceput);
        capacitateReziduala[nodInceput][i] = gradIntrare;

        listaAdiacenta[nodSfarsit].push_back(i + nrOrase);
        listaAdiacenta[i + nrOrase].push_back(nodSfarsit);
        capacitateReziduala[i + nrOrase][nodSfarsit] = gradIesire;
    }

    fin.close();
}

vector<bool> vizitat;
vector<int> tata;

bool BFS() {
    tata.clear();
    tata.resize(2 * nrOrase + 10, 0);

    vizitat.clear();
    vizitat.resize(2 * nrOrase + 10, false);

    queue<int> vecini;
    vecini.push(nodInceput);
    vizitat[nodInceput] = true;
    tata[nodInceput] = -1;

    // Parcurgere BFS pentru a găsi drumuri de creștere în graf
    while (!vecini.empty()) {
        int nodCurent = vecini.front();
        vecini.pop();

        if (nodCurent == nodSfarsit)
            continue;

        for (int vecin : listaAdiacenta[nodCurent])
            if (!vizitat[vecin] && capacitateReziduala[nodCurent][vecin] > 0) {
                tata[vecin] = nodCurent;
                vecini.push(vecin);
                vizitat[vecin] = true;
            }
    }

    return vizitat[nodSfarsit];
}

int fluxMaxim;

void EdmondsKarp() {
    // Algoritmul lui Edmonds-Karp pentru calculul fluxului maxim
    while (BFS()) {
        for (int vecin : listaAdiacenta[nodSfarsit]) {
            if (vizitat[vecin] && capacitateReziduala[vecin][nodSfarsit] > 0) {
                int fluxCrt = capacitateReziduala[vecin][nodSfarsit];

                // Calculam fluxul minim pe drumul de creștere
                for (int nodCrt = vecin; nodCrt != nodInceput; nodCrt = tata[nodCrt])
                    fluxCrt = min(fluxCrt, capacitateReziduala[tata[nodCrt]][nodCrt]);

                // Actualizam capacitatea reziduală
                capacitateReziduala[vecin][nodSfarsit] -= fluxCrt;
                capacitateReziduala[nodSfarsit][vecin] += fluxCrt;

                for (int nodCrt = vecin; nodCrt != nodInceput; nodCrt = tata[nodCrt]) {
                    capacitateReziduala[tata[nodCrt]][nodCrt] -= fluxCrt;
                    capacitateReziduala[nodCrt][tata[nodCrt]] += fluxCrt;
                }

                fluxMaxim += fluxCrt;
            }
        }
    }
}

void afisare() {
    ofstream fout("harta.out");

    fout << fluxMaxim << "\n";

    // Afisam muchiile din cuplaj
    for (int i = 1; i <= nrOrase; i++)
        for (int j = nrOrase + 1; j <= 2 * nrOrase; j++)
            if (capacitateReziduala[j][i] == 1)
                fout << i << " " << j - nrOrase << "\n";

    fout.close();
}

int main() {
    citire();
    EdmondsKarp();
    afisare();
    return 0;
}
