from collections import defaultdict,deque

class Solution(object):
    #https://leetcode.com/problems/possible-bipartition/
    def possibleBipartition(self,n,dislikes):
        # Crearea unui graf neorientat
        graph = defaultdict(list)
        for a, b in dislikes:
            # Adăugăm relațiile de antipatie între persoane din graf
            graph[a].append(b)
            graph[b].append(a)

        group = {}

        def dfs(node, g):
            # Verificam daca nodul a fost deja atribuit unui grup
            if node in group:
                # Ne asiguram ca acesta se afla în grupul corect
                return group[node] == g
            group[node] = g
            for neighbor in graph[node]:
                # Parcurgem vecinii nodului si verificam daca se pot atribui grupuri corecte
                if not dfs(neighbor, 3 - g):  # Schimbam grupul intre 1 și 2
                    return False

            return True

        for person in range(1, n + 1):
            if person not in group and not dfs(person, 1):
                return False

        return True


    #https://leetcode.com/problems/course-schedule-ii/
    def courseSchedule(self, numCourses, prerequisites):
        # Initializam un graf si un dictionar pentru a numara gradele de intrare
        graph = {i: [] for i in range(numCourses)}
        in_degree = {i: 0 for i in range(numCourses)}

        # Construim graful și calculăm gradele de intrare(cate cursuri trb luate inaintea acestuia)
        for course, prereq in prerequisites:
            graph[prereq].append(course)
            in_degree[course] += 1

        # Initializam o coada pentru cursurile cu grade de intrare zero
        queue = deque()
        for course in range(numCourses):
            if in_degree[course] == 0:
                queue.append(course)

        course_order = []
        while queue:
            course = queue.popleft()
            course_order.append(course) # Luam cursurile cu grad de intare 0 si le adaugam in lista
            for neighbor in graph[course]: # Apoi facem asta pt cursurile urmatoare
                in_degree[neighbor] -= 1
                if in_degree[neighbor] == 0:
                    queue.append(neighbor)

        # Verificam dacă am putut găsi o ordine valida a cursurilor
        if len(course_order) == numCourses:
            return course_order
        else:
            return []


    #https://leetcode.com/problems/critical-connections-in-a-network
    def criticalConnections(self, n, connections):
        # Initializam un graf
        graph = defaultdict(list)
        for a, b in connections:
            graph[a].append(b)
            graph[b].append(a)

        # Initializam lista muchhilor critice
        critic = []
        # Verificam daca un nod are o singura conexiune(fapt ce ar defini acea conexiune ca finnd critica)
        for key, value in graph.items():
            if len(value) <= 1:
                critic.append([key, value[0]])

        if (n == 2):
            return connections[0]
        else:
            return critic


    #https://leetcode.com/problems/find-eventual-safe-states/
    def eventualSafeNodes(self, graph):
        def isSafe(node):
            # Verificam daca nodul este sigur
            if node in safe_nodes:
                return True
            # Daca nodul are ciclu, nu este sigur
            if node in visiting:
                return False
            # Daca nodul nu a fost vizitat inca, il marcam ca vizitat
            visiting.add(node)
            # Exploram toți vecinii nodului
            for neighbor in graph[node]:
                if not isSafe(neighbor):
                    return False
            # Dupa ce am explorat toti vecinii, marcam nodul ca sigur
            visiting.remove(node)
            safe_nodes.add(node)
            return True

        safe_nodes = set()
        visiting = set()

        for node in range(len(graph)):
            isSafe(node)

        return sorted(list(safe_nodes))


    #https://leetcode.com/problems/shortest-bridge/
    def shortestBridge(self, grid):
        def findIsland():
            # Funcyie pentru a gasi insula si eticheta fiecare nod din insula
            for i in range(n):
                for j in range(m):
                    if grid[i][j] == 1:
                        # Folosim DFS pentru a eticheta insula curentă cu 2
                        labelIsland(i, j)
                        return

        def labelIsland(x, y):
            # DFS pentru a eticheta insula curentă
            stack = [(x, y)]  # Inițializam o stiva
            while stack:
                i, j = stack.pop()
                grid[i][j] = 2  # Etichetam insula curentă cu 2
                for dx, dy in directions:
                    ni, nj = i + dx, j + dy
                    # Verificam dacă vecinul are valoarea 1
                    if 0 <= ni < n and 0 <= nj < m and grid[ni][nj] == 1:
                        stack.append((ni, nj))

        def findMinBridge():
            # BFS
            # Initializam o coada in care adaugam toate elementele primei insule(cele care sunt egale cu 2)
            queue = deque([(x, y, 0) for x in range(n) for y in range(m) if grid[x][y] == 2])
            # Initializam un set pentru a urmari celulele deja vizitate în coada
            visited = set(queue)
            while queue:
                # Extragem o celula din coada si numarul de pasi parcurs
                x, y, steps = queue.popleft()
                for dx, dy in directions:
                    nx, ny = x + dx, y + dy
                    if 0 <= nx < n and 0 <= ny < m:
                        if grid[nx][ny] == 1: # Am gasit a doua insula
                            return steps

                        # Daca următoarea celula este apa si nu a fost vizitată inca,
                        # o adaugam în coada si marim nr de pasi
                        if grid[nx][ny] == 0 and (nx, ny) not in visited:
                            queue.append((nx, ny, steps + 1))
                            visited.add((nx, ny))

        n, m = len(grid), len(grid[0])
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]

        # Gasim prima insulă
        findIsland()

        # Gasim puntea minima
        min_bridge = findMinBridge()

        return min_bridge

    
    #https://leetcode.com/problems/satisfiability-of-equality-equations/
    def equationsPossible(self, equations):
        # Inițializăm o listă pentru a reprezenta grupurile variabilelor
        groups = [i for i in range(26)]

        def find(group):
            # Functie pentru a gasi grupul unei variabile
            if group != groups[group]:
                groups[group] = find(groups[group])
            return groups[group]

        for eq in equations:
            if eq[1] == "=":
                # Daca avem o ecuatie de tip "xi==yi", unim grupurile variabilelor xi și yi
                x, y = ord(eq[0]) - ord("a"), ord(eq[3]) - ord("a")
                groups[find(x)] = find(y)

        # Verificam ecuațiile de tip "xi!=yi" pentru a asigura ca variabilele nu sunt în același grup
        for eq in equations:
            if eq[1] == "!" and find(ord(eq[0]) - ord("a")) == find(ord(eq[3]) - ord("a")):
                return False

        return True
