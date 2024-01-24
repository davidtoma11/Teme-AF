#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <climits>

using namespace std;

ifstream fin("cc.in");
ofstream fout("cc.out");

int costs[202][202];

class Graph
{
    vector<vector<int>> edges;
    map<pair<int, int>, int> edgeValues; // Mapeaza perechile de noduri la costurile muchiilor
    int numNodes;

public:
    Graph(int n = 1) : numNodes(n)
    {
        edges = vector<vector<int>>(n + 1);
    }

    // Adaugă o muchie între nodurile x și y cu un cost opțional
    void addEdge(int x, int y, int cost = 0)
    {
        edges[x].push_back(y);
        edgeValues[{x, y}] = cost;
    }

    // Setează valoarea unei muchii
    void setEdgeValue(int x, int y, int newValue)
    {
        edgeValues[{x, y}] = newValue;
    }

    // Obține valoarea unei muchii
    int getEdgeValue(int x, int y)
    {
        return edgeValues[{x, y}];
    }

    // Algoritmul de BFS pentru determinarea fluxului maxim
    void maxFlowBFS(vector<int> &parents, int start, int sink)
    {
        queue<pair<int, int>> q;
        q.push(make_pair(start, INT_MAX));
        vector<int> minCost(numNodes, INT_MAX), inQueue(numNodes, 0);
        parents[start] = start;
        minCost[start] = 0;

        while (!q.empty())
        {
            int currentNode = q.front().first, maxFlow = q.front().second;
            inQueue[currentNode] = 0;

            for (auto &neighbor : edges[currentNode])
            {
                if (edgeValues[{currentNode, neighbor}] > 0 && minCost[neighbor] > minCost[currentNode] + costs[currentNode][neighbor])
                {
                    minCost[neighbor] = minCost[currentNode] + costs[currentNode][neighbor];
                    parents[neighbor] = currentNode;

                    if (!inQueue[neighbor])
                    {
                        inQueue[neighbor] = 1;
                        q.push(make_pair(neighbor, min(edgeValues[{currentNode, neighbor}], maxFlow)));
                    }
                }
            }
            q.pop();
        }
    }

    // Funcția principală pentru calculul fluxului maxim
    void maxFlow(int n)
    {
        int result = 0;               // Variabila pentru a urmări rezultatul final al fluxului maxim
        vector<int> parents(202, -1); // Vector pentru a urmări părinții într-un drum de creștere
        parents[201] = 201;           // Inițializăm părintele nodului final cu o valoare validă

        // Continuăm să căutăm drumuri de creștere până când nu mai există
        while (parents[201] != -1)
        {
            parents.assign(202, -1);     // Resetăm vectorul de părinți pentru fiecare iterație
            maxFlowBFS(parents, 0, 201); // Apelăm BFS pentru a găsi un drum de creștere

            // Verificăm dacă am găsit un drum de creștere
            if (parents[201] != -1)
            {
                int currentNode = 201; // Inițializăm nodul curent cu nodul final

                // Refacem drumul de creștere și ajustăm capacitatea reziduală
                while (currentNode != 0)
                {
                    // Reducem capacitatea pe muchia de intrare în nodul curent și
                    // creștem capacitatea pe muchia de ieșire din nodul curent
                    edgeValues[{parents[currentNode], currentNode}] -= 1;
                    edgeValues[{currentNode, parents[currentNode]}] += 1;
                    currentNode = parents[currentNode]; // Trecem la părintele următor
                }
            }
        }
    }

    // Calculul rezultatului final
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (edgeValues[{100 + j, i}] > 0)
            {
                result += costs[i][100 + j];
            }
        }
    }

    // Scrierea rezultatului în fișierul de ieșire
    fout << result << '\n';
}
}
;

int main()
{
    int n;
    fin >> n;
    Graph g(202);

    // Citirea
    for (int i = 1; i <= n; i++)
    {
        g.addEdge(0, i, 1);
        g.addEdge(i, 0, 0);
        g.addEdge(100 + i, 201, 1);
        g.addEdge(201, 100 + i, 0);

        for (int j = 1; j <= n; j++)
        {
            fin >> costs[i][100 + j];
            costs[100 + j][i] -= costs[i][100 + j];
            g.addEdge(i, 100 + j, 1);
            g.addEdge(100 + j, i, 0);
        }
    }

    // Calculul fluxului maxim și scrierea rezultatului
    g.maxFlow(n);

    return 0;
}
