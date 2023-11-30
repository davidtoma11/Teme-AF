class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // Cream o reprezentare a grafului sub forma de listă de adiacență
        vector<vector<pair<int, int>>> graph(n);

        // Construim graful
        for (auto &entry : flights) {
            int s = entry[0], d = entry[1], price = entry[2];
            graph[s].push_back({d, price});
        }

        // Vector pentru stocarea celui mai bun pret pana la fiecare nod
        vector<int> bestPrice(n, INT_MAX);

        // Coada pentru parcurgerea grafului
        queue<pair<int, int>> q;
        q.push({src, 0});

        // Parcurgem graful folosind BFS cu limită pe numărul de opriri (k)
        while (k >= 0 && !q.empty()) {
            int level = q.size();

            while (level--) {
                auto [cur, price] = q.front();
                q.pop();

                // Parcurgem vecinii nodului curent
                for (auto &[next, cost] : graph[cur]) {
                    int nextPrice = price + cost;
                    // Verificăm dacă avem o soluție mai bună
                    if (nextPrice >= bestPrice[next]) continue;
                    bestPrice[next] = nextPrice;

                    // Verificam dacă am ajuns la destinație
                    if (next == dst) continue;

                    // Adaugam următorul nod în coadă
                    q.push({next, nextPrice});
                }
            }
            k--;
        }

        return bestPrice[dst] == INT_MAX ? -1 : bestPrice[dst];
    }
};
