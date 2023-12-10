#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>

#define MAX_NODES 50002
#define INF 400000000

using namespace std;

int nodes, edges, maxWeight, distances[MAX_NODES], heapSize, heap[MAX_NODES], positions[MAX_NODES];
ifstream input("camionas.in");
ofstream output("camionas.out");
vector<pair<int, int>> graph[MAX_NODES];

// Funcție pentru citirea datelor de intrare
void readInput() {
    input >> nodes >> edges >> maxWeight;
    int from, to, weight;
    for (int i = 0; i < edges; ++i) {
        input >> from >> to >> weight;
        weight = (maxWeight > weight) ? 1 : 0;
        graph[from].push_back(make_pair(to, weight));
        graph[to].push_back(make_pair(from, weight));
    }
}

// Funcție pentru a returna indicele copilului stâng al unui nod într-un heap
int leftChild(int k) {
    return 2 * k;
}

// Funcție pentru a returna indicele copilului drept al unui nod într-un heap
int rightChild(int k) {
    return 2 * k + 1;
}

// Funcție pentru inițializarea datelor
void initialize() {
    for (int i = 2; i <= nodes; ++i)
        distances[i] = INF;
    heapSize = 0;
    heap[++heapSize] = 1;
    positions[1] = 1;
}

// Funcție pentru percolarea unui nod în sus într-un heap
void percolate(int k) {
    while (k > 1 && distances[heap[k]] < distances[heap[k / 2]]) {
        swap(positions[heap[k]], positions[heap[k / 2]]);
        swap(heap[k], heap[k / 2]);
        k /= 2;
    }
}

// Funcție pentru siftarea unui nod în jos într-un heap
void sift(int k) {
    int son = k;
    if (leftChild(k) <= heapSize && distances[heap[leftChild(k)]] < distances[heap[son]])
        son = leftChild(k);
    if (rightChild(k) <= heapSize && distances[heap[rightChild(k)]] < distances[heap[son]])
        son = rightChild(k);
    if (son != k) {
        swap(positions[heap[k]], positions[heap[son]]);
        swap(heap[k], heap[son]);
        sift(son);
    }
}

// Funcție pentru extragerea minimului din heap
void extractMin(int &minNode) {
    minNode = heap[1];
    heap[1] = heap[heapSize--];
    positions[heap[1]] = 1;
    sift(1);
}

// Funcție pentru inserarea unui nod în heap
void insert(int node) {
    heap[++heapSize] = node;
    positions[node] = heapSize;
    percolate(positions[node]);
}

// Algoritmul lui Dijkstra pentru găsirea celui mai scurt drum
void dijkstra() {
    for (; heapSize;) {
        int minNode;
        extractMin(minNode);
        int current = minNode;
        for (int i = 0; i < graph[current].size(); ++i) {
            int neighbor = graph[current][i].first;
            if (distances[neighbor] > distances[current] + graph[current][i].second) {
                distances[neighbor] = distances[current] + graph[current][i].second;
                if (positions[neighbor])
                    percolate(positions[neighbor]);
                else
                    insert(neighbor);
            }
        }
    }
}

// Funcție pentru afișarea rezultatului
void printOutput() {
    output << distances[nodes] << "\n";
}

int main() {
    readInput();
    initialize();
    dijkstra();
    printOutput();
    return 0;
}
