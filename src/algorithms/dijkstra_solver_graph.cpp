#include <vector>
#include <queue>
#include <set>
#include <iostream>
#include <./graph.h>
#include <./mazemap.h>
#include <algorithms/algorithms.h>
#include <map>
#include <climits>
#include <algorithm>
#ifdef __GNUC__
#include <bits/algorithmfwd.h>
#endif

std::vector<int> Algorithms::dijkstra(MazeGraph& graph, int startNode, int endNode, std::vector<int>& visitOrder) {
    std::set<int> visited;               // Set of visited nodes
    std::map<int, int> dist;             // Shortest distances from the start node
    std::map<int, int> prev;             // Predecessors of nodes on the shortest path

    // Initialize distances and predecessors
    for (int i = 0; i < graph.GetNumVertices(); ++i) {
        dist[i] = INT_MAX;
        prev[i] = -1;
    }
    dist[startNode] = 0;

    // Priority queue for processing nodes
    using Node = std::pair<int, int>;  // (distance, node)
    std::priority_queue<Node, std::vector<Node>, std::greater<>> pq;
    pq.push({0, startNode});

    while (!pq.empty()) {
        auto [currentDist, currentNode] = pq.top();
        pq.pop();

        // If the node has already been visited, skip it
        if (visited.find(currentNode) != visited.end()) {
            continue;
        }

        visited.insert(currentNode);
        visitOrder.push_back(currentNode);  // Add to the list of visited nodes

        //std::cout << "Visiting node " << currentNode << " with distance " << currentDist << std::endl;

        // Check if the end node has been reached
        if (currentNode == endNode) {
            //std::cout << "Reached end node: " << endNode << std::endl;
            break;
        }

        // Process neighbors
        for (int neighbor : graph.GetAdjacentNodeIndicies(currentNode)) {
            if (visited.find(neighbor) != visited.end()) {
                continue;
            }

            int newDist = dist[currentNode] + 1;  // Edge weight = 1
            if (newDist < dist[neighbor]) {
                dist[neighbor] = newDist;
                prev[neighbor] = currentNode;
                pq.push({newDist, neighbor});
                //std::cout << "Updating distance of node " << neighbor << " to " << newDist << std::endl;
            }
        }
    }

    // Reconstruct the path
    std::vector<int> path;
    for (int at = endNode; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());

    // Check if the path starts from the start node
    if (path.front() != startNode) {
        std::cout << "No path found from " << startNode << " to " << endNode << std::endl;
        return {};
    }

    return path;
}