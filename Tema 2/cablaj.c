#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

ifstream fin("cablaj.in");
ofstream fout("cablaj.out");

struct Punct
{
    int x, y;
};

Punct a[3002];
int n;
double costMinim;
int d[3002], viz[3002];

// Funcție pentru calculul distanței euclidiene între două puncte
int Dist(Punct A, Punct B)
{
    return (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y);
}

void Citire()
{
    fin >> n;
    for (int i = 1; i <= n; i++)
        fin >> a[i].x >> a[i].y;
}

// Algoritmul lui Prim pentru calculul Arborelui de Acoperire Minim (APM)
void Prim()
{
    int i, k, minim, dist;

    // Inițializare
    d[1] = 0;
    viz[1] = 1;

    // Inițializare distanțe inițiale
    for (i = 2; i <= n; i++)
        d[i] = Dist(a[1], a[i]);

    // Pas principal pentru construirea APM
    for (int pas = 2; pas <= n; pas++)
    {
        // Aflăm valoarea minimă d[k] pentru un nod nevizitat
        minim = 2e9;
        k = 0;

        for (i = 2; i <= n; i++)
            if (viz[i] == 0 && d[i] < minim)
            {
                minim = d[i];
                k = i;
            }

        // Marcam nodul k ca vizitat
        viz[k] = 1;
        costMinim += sqrt(d[k]);

        // Actualizăm distanțele
        for (i = 2; i <= n; i++)
        {
            dist = Dist(a[k], a[i]);
            if (viz[i] == 0 && d[i] > dist)
                d[i] = dist;
        }
    }

    // Afisăm costul minim cu precizie de 4 zecimale
    fout << setprecision(4) << fixed << costMinim << "\n";
}

int main()
{
    Citire();
    Prim();
    return 0;
}
