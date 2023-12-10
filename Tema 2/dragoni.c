#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>

#define ll long long
#define pb push_back
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

ifstream in("dragoni.in");
ofstream out("dragoni.out");

const int NMAX = 805;
const char nl = '\n';
const int INF = 1e9;

struct dragon {
    int x, type, w;
    bool operator<(const dragon &aux) const {
        return w > aux.w;
    }
};

int q, n, m, dmax = -INF, capacity[NMAX], f[NMAX], dist[NMAX][NMAX];

vector<pii> v[NMAX];

priority_queue<dragon> pq;

// Funcție DFS pentru a găsi capacitatea maximă pe care o poate transporta dragonul
void dfs(int node) {
    f[node] = 1;
    if (capacity[node] > dmax)
        dmax = capacity[node];
    for (auto i : v[node]) {
        if (!f[i.x] && i.y <= capacity[1])
            dfs(i.x);
    }
}

// Algoritmul lui Dijkstra pentru a găsi distanța minimă între nodul 1 și celelalte noduri
void dijkstra() {
    dist[1][1] = 0;
    pq.push({1, 1, 0});
    while (!pq.empty()) {
        int cur_node = pq.top().x;
        int cur_type = pq.top().type;
        int cur_weight = pq.top().w;

        pq.pop();

        if (capacity[cur_node] > capacity[cur_type]) {
            dist[cur_node][cur_node] = min(dist[cur_node][cur_node], dist[cur_node][cur_type]);
            cur_type = cur_node;
        }

        for (auto neigh : v[cur_node]) {
            if (dist[neigh.x][cur_type] > cur_weight + neigh.y && neigh.y <= capacity[cur_type]) {
                dist[neigh.x][cur_type] = cur_weight + neigh.y;
                pq.push({neigh.x, cur_type, dist[neigh.x][cur_type]});
            }
        }
    }
}

int main() {
    in >> q >> n >> m;
    for (int i = 1; i <= n; ++i)
        in >> capacity[i];
    for (int i = 1; i <= m; ++i) {
        int a, b, c;
        in >> a >> b >> c;
        v[a].pb({b, c});
        v[b].pb({a, c});
    }

    if (q == 1) {
        // Dacă cerința este de tipul 1, se aplică DFS pentru a găsi capacitatea maximă
        dfs(1);
        out << dmax << nl;
    } else {
        // Dacă cerința este de tipul 2, se aplică algoritmul lui Dijkstra pentru a găsi distanța minimă
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                dist[i][j] = INF;
            }
        }
        dijkstra();
        dmax = INF;
        for (int i = 1; i <= n; ++i)
            dmax = min(dmax, dist[n][i]);
        out << dmax << nl;
    }

    return 0;
}
