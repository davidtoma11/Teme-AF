from array import array
class Solution:
    def validArrangement(self, pairs: List[List[int]]) -> List[List[int]]:
        # Crearea unui graf și calculul gradului nodurilor
        graph = defaultdict(lambda: array('I'))
        degree = defaultdict(int)  # gradul de iesire al nodurilor
        for y, x in pairs:
            graph[x].append(y)
            degree[x] += 1
            degree[y] -= 1

        # Inițializarea stivei cu primul nod cu grad de ieșire 1 (sau oricare nod disponibil)
        stack = array('I', [next((k for k in graph if degree[k] == 1), x)])

        # Construim calea folosind DFS
        while (l := graph[stack[-1]]):
            stack.append(l.pop())

        prev = stack.pop()

        # Refacem calea folosind DFS si generarea de perechi
        while stack:
            while (l := graph[stack[-1]]):
                stack.append(l.pop())
            yield (prev, (prev := stack.pop()))
