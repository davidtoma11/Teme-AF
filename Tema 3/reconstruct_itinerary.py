class Solution:
    def findItinerary(self, tickets) -> list[str]:
        # Graful zborurilor, reprezentat sub forma unui dicționar
        flightGraph = defaultdict(list)
        # Lista pentru itinerariul de calatorie
        travelItinerary = []

        # Construirea grafului
        for ticket in tickets:
            fromAirport, toAirport = ticket[0], ticket[1]
            flightGraph[fromAirport].append(toAirport)

        # Sortarea destinatiilor pentru fiecare aeroport (ordine DESC)
        for destinations in flightGraph.values():
            destinations.sort(reverse=True)

        # Stiva pentru DFS începută cu aeroportul JFK
        dfsStack = ["JFK"]

        # Parcurgerea grafului folosind DFS
        while dfsStack:
            currentAirport = dfsStack[-1]
            destinations = flightGraph.get(currentAirport, [])

            if destinations:
                # Extrage următoarea destinație și adaugă în stivă
                nextDestination = destinations.pop()
                dfsStack.append(nextDestination)
            else:
                # Adauga aeroportul curent în itinerariu și elimină din stiva
                travelItinerary.append(currentAirport)
                dfsStack.pop()

        # Reverseaza itinerariul pentru a obține ordinea corectă
        travelItinerary.reverse()
        return travelItinerary