#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <utility>
#include <climits>
#include <algorithm> // Needed for std::reverse
#include "labirynthdata.h"

// Graph structure storing neighbors for each cell in the labyrinth
using Graph = std::unordered_map<int, std::vector<int>>;

// Converts the labyrinth into a graph (nodes and edges between cells)
Graph buildGraph(const Labirynth& labirynth) {
    int rows = labirynth.getRows();
    int cols = labirynth.getCols();
    Graph graph;

    // Direction vectors for moving up, down, left, right
    const int dx[] = {-1, 1, 0, 0};
    const int dy[] = {0, 0, -1, 1};

    // Iterate over each cell in the labyrinth
    for (int x = 0; x < rows; ++x) {
        for (int y = 0; y < cols; ++y) {
            // Only proceed if the current cell is not a wall
            if (!labirynth.isWall(x, y)) {
                int node = x * cols + y; // Index in the graph

                // Check four possible neighboring cells (up, down, left, right)
                for (int i = 0; i < 4; ++i) {
                    int nx = x + dx[i];
                    int ny = y + dy[i];

                    // Add valid neighbors that are within bounds and are not walls
                    if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && !labirynth.isWall(nx, ny)) {
                        int neighbor = nx * cols + ny;
                        graph[node].push_back(neighbor);
                    }
                }
            }
        }
    }
    return graph;
}

// Solves the labyrinth using Dijkstra's algorithm with the graph structure
std::vector<std::pair<int, int>> solveMazeDijkstraGraph(Labirynth& labirynth) {
    int rows = labirynth.getRows();
    int cols = labirynth.getCols();
    int start = 0;             // Starting node (top-left corner)
    int end = rows * cols - 1; // Ending node (bottom-right corner)

    // Build the labyrinth's graph representation
    Graph graph = buildGraph(labirynth);

    // Initialize distance and predecessor vectors
    std::vector<int> dist(rows * cols, INT_MAX); // Distance to each node, initially set to infinity
    dist[start] = 0;
    std::vector<int> prev(rows * cols, -1); // To keep track of path predecessors

    // Priority queue for processing nodes by shortest distance
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
    pq.push({0, start}); // Start with the initial node with distance 0

    // Dijkstra's algorithm on the graph
    while (!pq.empty()) {
        auto [d, node] = pq.top();
        pq.pop();

        // If we reached the target node, break out of the loop
        if (node == end) break;

        // Traverse each neighbor of the current node
        for (int neighbor : graph[node]) {
            int new_dist = d + 1; // Edge cost between nodes (always 1 for adjacent cells)

            // If a shorter path to neighbor is found, update the distance and push to queue
            if (new_dist < dist[neighbor]) {
                dist[neighbor] = new_dist;
                prev[neighbor] = node; // Store the predecessor for path reconstruction
                pq.push({new_dist, neighbor});
            }
        }
    }

    // Reconstruct the path from the end node to the start using predecessors
    std::vector<std::pair<int, int>> path;
    for (int at = end; at != -1; at = prev[at]) {
        path.push_back({at / cols, at % cols}); // Convert linear index to 2D coordinates
    }

    std::reverse(path.begin(), path.end()); // Reverse the path to start from the beginning

    // If the first cell in the path is not the start, it means no valid path was found
    if (path.front() != std::make_pair(0, 0)) {
        path.clear(); // Clear the path if it doesn't start at the entry
    }

    return path;
}

// Function to print the path
void printPath(const std::vector<std::pair<int, int>>& path) {
    if (path.empty()) {
        std::cout << "No available path.\n";
    } else {
        std::cout << "Path:\n";
        for (const auto& [x, y] : path) {
            std::cout << "(" << x << ", " << y << ") -> ";
        }
        std::cout << "End\n";
    }
}

int main() {
    // Create a sample labyrinth with dimensions 5x6
    Labirynth labirynth(5, 6);

    // Mark specific cells as walls
    labirynth.MarkWall(0, 1);
    labirynth.MarkWall(1, 1);
    labirynth.MarkWall(1, 3);
    labirynth.MarkWall(1, 4);
    labirynth.MarkWall(1, 5);
    labirynth.MarkWall(3, 0);
    labirynth.MarkWall(3, 2);
    labirynth.MarkWall(3, 3);

    std::cout << "Labyrinth:\n";
    labirynth.Print();

    // Run Dijkstra's algorithm to find the shortest path
    std::vector<std::pair<int, int>> path = solveMazeDijkstraGraph(labirynth);

    // Display the resulting path
    printPath(path);

    return 0;
}
