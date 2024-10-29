#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// edge representation
typedef pair<int, int> Edge;

class Graph {
private:
  int vertices; // number of vertices
  vector<vector<Edge>> adjacencyList; 

public:
  // creating graph with given number of vertices
  Graph(int v) : vertices(v) {
      adjacencyList.resize(v);
  }

  // add edge to graph
  void addEdge(int u, int v, int weight) {
      adjacencyList[u].push_back({weight, v});
      adjacencyList[v].push_back({weight, u}); // if the graph is not directed 
  }

  // main algorithm
  vector<int> dijkstra(int start) {
      vector<int> distances(vertices, numeric_limits<int>::max());
      distances[start] = 0;

      priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
      pq.push({0, start});

      while (!pq.empty()) {
          int current_distance = pq.top().first;
          int current_vertex = pq.top().second;
          pq.pop();

          if (current_distance > distances[current_vertex])
              continue;

          for (const Edge& neighbor : adjacencyList[current_vertex]) {
              int weight = neighbor.first;
              int neighbor_vertex = neighbor.second;

              int distance_through_current = current_distance + weight;
              if (distance_through_current < distances[neighbor_vertex]) {
                  distances[neighbor_vertex] = distance_through_current;
                  pq.push({distance_through_current, neighbor_vertex});
              }
          }
      }

      return distances;
  }
};

int main() {
  int n, m;
  cout << "Enter number of vertices and edges: ";
  cin >> n >> m;

  Graph graph(n);

  cout << "Enter edges in format: vertex1 vertex2 distance\n";
  for (int i = 0; i < m; ++i) {
      int u, v, w;
      cin >> u >> v >> w;
      graph.addEdge(u, v, w);
  }

  int start;
  cout << "Enter start-vertex: ";
  cin >> start;

  vector<int> distances = graph.dijkstra(start);

  cout << "Shortest distances from vertex " << start << ":\n";
  for (int i = 0; i < distances.size(); ++i) {
      cout << "to vertex " << i << " = ";
      if (distances[i] == numeric_limits<int>::max()) {
          cout << "UNREACHABLE\n";
      } else {
          cout << distances[i] << "\n";
      }
  }

  return 0;
}
