#include <vector>
#include <queue>
#include <set>
#include <iostream>
#include <../graph.h>
#include <../mazemap.h>
#include <map>
#include <climits>
#include <bits/algorithmfwd.h>

std::vector<int> dijkstra(MazeGraph& graph, int startNode, int endNode, std::vector<int>& visitOrder) {
    std::set<int> visited;  // Zbiór odwiedzonych węzłów
    std::map<int, int> dist;  // Najkrótsze dystanse
    std::map<int, int> prev;  // Poprzedniki węzłów

    // Inicjalizacja dystansów
    for (int i = 0; i <= startNode; ++i) {
        dist[i] = INT_MAX;
    }
    dist[startNode] = 0;

    // Kolejka priorytetowa do przetwarzania węzłów
    using Node = std::pair<int, int>;  // (dystans, węzeł)
    std::priority_queue<Node, std::vector<Node>, std::greater<>> pq;
    pq.push({0, startNode});

    while (!pq.empty()) {
        auto [currentDist, currentNode] = pq.top();
        pq.pop();

        // Sprawdź, czy węzeł został już odwiedzony
        if (visited.find(currentNode) != visited.end()) {
            continue;
        }

        visited.insert(currentNode);
        visitOrder.push_back(currentNode);  // Dodaj do odwiedzonych węzłów

        // Przerwij, jeśli dotarliśmy do końca
        if (currentNode == endNode) {
            break;
        }

        // Przetwarzanie sąsiadów
        for (int neighbor : graph.GetAdjacentNodeIndicies(currentNode)) {
            if (visited.find(neighbor) != visited.end()) {
                continue;
            }

        // Sprawdź, czy nowa ścieżka do sąsiada jest krótsza; jeśli tak, zaktualizuj dystans i dodaj do kolejki
            int newDist = dist[currentNode] + 1;  // Waga krawędzi = 1
            if (newDist < dist[neighbor]) {
                dist[neighbor] = newDist;
                prev[neighbor] = currentNode;
                pq.push({newDist, neighbor});
            }
        }
    }

    // Rekonstrukcja ścieżki
    std::vector<int> path;
    for (int at = endNode; at != 0; at = prev[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());

    return path.front() == startNode ? path : std::vector<int>{};
}

int main() {
    // Tworzenie mapy labiryntu (na razie z ręcznym wypisaniem ścian)
   MazeMap maze(10, 10, {
        {0, 1}, {0, 3}, {0, 5}, {0, 7}, {0, 9},
        {1, 1}, {1, 3}, {1, 5}, {1, 7}, {1, 9},
        {2, 1}, {2, 3}, {2, 5}, {2, 7}, {2, 9},
        {3, 3}, {3, 5}, {3, 7},
        {4, 1}, {4, 3}, {4, 5}, {4, 7}, {4, 9},
        {5, 3}, {5, 5}, {5, 7},
        {6, 1}, {6, 3}, {6, 5}, {6, 7}, {6, 9},
        {7, 1}, {7, 3}, {7, 5}, {7, 7}, {7, 9},
        {8, 1}, {8, 3}, {8, 5}, {8, 7}, {8, 9},
        {9, 1}, {9, 3}, {9, 5}, {9, 7}, {9, 9}
    });
    maze.Print();

    // Tworzenie grafu na podstawie mapy
    MazeGraph graph = maze.ToMazeGraph(1, 1);  // Start grafu od punktu (1, 1)

    // Węzły startowy i końcowy
    int startNode = graph.GetIndexFromCoords(1, 1);
    int endNode = graph.GetIndexFromCoords(8, 8);

    // Algorytm Dijkstry
    std::vector<int> visitOrder; // Wektor przechowujący kolejność odwiedzanych węzłów podczas działania algorytmu
    std::vector<int> path = dijkstra(graph, startNode, endNode, visitOrder);

    // Wyświetlenie wyników
    if (path.empty()) {
        std::cout << "Brak dostępnej ścieżki.\n";
    } else {
        std::cout << "Ścieżka: ";
        for (int node : path) {
            auto coords = graph.GetGraphNode(node);  // Współrzędne węzła
            std::cout << "(" << coords->x << ", " << coords->y << ") -> ";
        }
        std::cout << "Koniec\n";
    }

    return 0;
}