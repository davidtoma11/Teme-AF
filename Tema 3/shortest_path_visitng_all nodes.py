class Solution:
    def shortestPathLength(self, graph: List[List[int]]) -> int:
        q = deque()  # Coada pentru BFS
        s = set()    # Set pentru a urmari starile vizitate
        n = len(graph)

        # Initializam coada cu nodurile initiale și setul cu starea initială
        for i in range(n):
            q.append([i, 0, 1 << i])  # Nod, distanța, masca de stari vizitate
            s.add((i, 1 << i))  # Tuplu (nod, masca)

        reached = (1 << n) - 1  # Masca pentru toate nodurile atinse

        while len(q) > 0:
            node, dis, mask = q.popleft()
            
            if mask == reached:
                return dis  # Am atins toate nodurile

            for nei in graph[node]:
                tempMask = mask | 1 << nei  # Actualizam masca cu noul nod
                if (nei, tempMask) not in s:
                    s.add((nei, tempMask))
                    # Adaugam vecinii în coada cu distanta si masca actualizate
                    q.append([nei, dis + 1, tempMask])  

        return 0 