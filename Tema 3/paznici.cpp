#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

ifstream fin("paznici.in");
ofstream fout("paznici.out");

const int NMax = 26;

int N, M, L[NMax + 5], R[NMax + 5];
char x;
bool Use[NMax + 5], useL[NMax + 5], useR[NMax + 5];

vector<int> G[NMax + 5];

// Verifica daca un nod poate forma un cuplaj
bool Cuplaj(int Nod)
{
    if (Use[Nod])
        return 0;
    Use[Nod] = 1;

    for (auto Vecin : G[Nod])
        if (R[Vecin] == 0)
        {
            L[Nod] = Vecin;
            R[Vecin] = Nod;
            return 1;
        }

    for (auto Vecin : G[Nod])
        if (R[Vecin] && Cuplaj(R[Vecin]))
        {
            L[Nod] = Vecin;
            R[Vecin] = Nod;
            return 1;
        }
    return 0;
}

// Algoritmul lui Hopcroft-Karp pentru găsirea unui cuplaj maxim
void Solve()
{
    bool ok;

    do
    {
        ok = 0;
        memset(Use, 0, sizeof(Use));

        for (int i = 1; i <= N; i++)
            if (!L[i])
                ok |= Cuplaj(i);
    } while (ok);
}

// Functia recursiva pentru "cuplarea" nodurilor din partea stanga si dreapta
void PairUp(int Nod)
{
    for (auto Vecin : G[Nod])
        if (!useR[Vecin])
        {
            useR[Vecin] = 1;
            useL[R[Vecin]] = 0;
            PairUp(R[Vecin]);
        }
}

// Găsește nodurile care nu au fost "cuplate"
void Suport()
{
    for (int i = 1; i <= N; i++)
        useL[i] = (L[i] != 0);

    for (int i = 1; i <= N; i++)
        if (!useL[i])
            PairUp(i);
}

int main()
{
    fin >> N >> M;

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++)
        {
            fin >> x;

            if (x == '1')
                G[i].push_back(j);
        }
    Solve();
    Suport();

    // Afisare rezultat
    for (int i = 1; i <= N; i++)
        if (useL[i])
            fout << (char)('A' + i - 1);

    for (int i = 1; i <= M; i++)
        if (useR[i])
            fout << (char)('a' + i - 1);

    fin.close();
    fout.close();

    return 0;
}
