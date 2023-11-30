#include <cmath>
#include <fstream>
#include <iomanip>
#include <limits>
#include <vector>
#include <utility>
using namespace std;

// Definim un tip de date pentru a reprezenta un oras cu coordonate (x, y)
typedef pair<int, int> City;

// Funcție care calculează distanța euclidiană dintre două orașe
double calculateDistance(const City &a, const City &b)
{
    return sqrt(pow(a.first - b.first, 2.0) + pow(a.second - b.second, 2.0));
}

int main()
{
    // Deschidem fișierul de intrare
    ifstream inputFile("input.in");

    // Citim numărul de orașe din fișierul de intrare
    int numCities;
    inputFile >> numCities;

    // Inițializăm vectorii și variabilele necesare pentru algoritmul de calculare a arborelui de acoperire minimă
    vector<City> cities(numCities + 1);
    vector<double> distance(numCities + 1, numeric_limits<double>::max());
    vector<bool> visited(numCities + 1, false);
    visited[1] = true;

    // Citim coordonatele fiecărui oraș din fișierul de intrare
    for (int i = 1; i <= numCities; i++)
        inputFile >> cities[i].first >> cities[i].second;

    // Inițializăm costul total al cablajului
    double totalCost = 0;

    // Inițializăm distanțele de la primul oraș la celelalte orașe
    for (int i = 1; i <= numCities; i++)
        distance[i] = calculateDistance(cities[1], cities[i]);

    // Algoritmul de calculare a arborelui de acoperire minimă (Prim's Algorithm)
    for (int i = 1; i < numCities; i++)
    {
        int minIndex = 0;

        // Găsim cel mai apropiat oraș nevizitat
        for (int j = 2; j <= numCities; j++)
            if (!visited[j] && distance[j] < distance[minIndex])
                minIndex = j;

        // Adăugăm distanța minimă la costul total
        totalCost += distance[minIndex];
        visited[minIndex] = true;

        // Actualizăm distanțele față de arborele curent
        for (int j = 2; j <= numCities; j++)
            if (!visited[j])
                distance[j] = min(distance[j], calculateDistance(cities[minIndex], cities[j]));
    }

    // Deschidem fișierul de ieșire și scriem costul total cu precizie de 3 zecimale
    ofstream outputFile("output.out");
    outputFile << setiosflags(ios::fixed) << setprecision(3) << totalCost;

    // Închidem fișierele și terminăm programul
    return 0;
}