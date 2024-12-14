#include "mazemap.h"
#include <iostream>
#include <fstream>
#include "algorithms/algorithms.h"
#include <filesystem>
#include "serialize.h"

bool isFileValid(const char *fileName)
{
    std::ifstream f(fileName);
    return f.good();
}

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        std::cout << "Usage: " << argv[0] << "<file>" << std::endl;
        return 1;
    }
    const char* filename = argv[1];
    if(!isFileValid(filename))
    {
        std::cout << "File not found: " << filename << std::endl;
        return 1;
    }
    std::filesystem::create_directory("output");
    MazeMap mazeMap(filename);
    MazeGraph mazeGraph = mazeMap.ToMazeGraph();
    // dfs
    std::vector<int> dfsNodeVisitOrder;
    std::vector<int> dfsPath = Algorithms::dfs(mazeGraph, 0, mazeGraph.GetIndexFromCoords(12, 4), dfsNodeVisitOrder);
    std::vector<std::shared_ptr<MazeGraphNode>> nodes;
    std::vector<std::shared_ptr<MazeGraphNode>> history;
    for(auto node : dfsPath)
    {
        nodes.push_back(mazeGraph.GetGraphNode(node));
    }
    for(auto node : dfsNodeVisitOrder)
    {
        history.push_back(mazeGraph.GetGraphNode(node));
    }
    //WriteGraphNodesToFile("output/dfs_path.bin", nodes);
    WriteGraphNodesToTextFile("output/dfs_path.txt", nodes);
    WriteGraphNodesToTextFile("output/dfs_visit_order.txt", history);

    // bfs
    std::vector<int> bfsNodeVisitOrder;
    std::vector<int> bfsPath = Algorithms::bfs(mazeGraph, 0, mazeGraph.GetIndexFromCoords(12, 4), bfsNodeVisitOrder);
    nodes.clear();
    history.clear();
    for(auto node : bfsPath)
    {
        nodes.push_back(mazeGraph.GetGraphNode(node));
    }
    for(auto node : bfsNodeVisitOrder)
    {
        history.push_back(mazeGraph.GetGraphNode(node));
    }

    //WriteGraphNodesToFile("output/bfs_path.bin", nodes);
    WriteGraphNodesToTextFile("output/bfs_path.txt", nodes);
    WriteGraphNodesToTextFile("output/bfs_visit_order.txt", history);

    // Dijkstra

/*
    std::cout << "MazeGraph nodes and their neighbors:" << std::endl;

    for (int node = 0; node < mazeGraph.GetNumVertices(); ++node) { 
        auto coords = mazeGraph.GetGraphNode(node); // Get the coordinates of the node
        if (!coords) continue; // Check if the node exists (in case of empty nodes)

        std::cout << "Node " << node << " at coords (" << coords->x << ", " << coords->y << ") has neighbors: ";
        for (int neighbor : mazeGraph.GetAdjacentNodeIndicies(node)) { // Get the neighbors of the node
            auto neighborCoords = mazeGraph.GetGraphNode(neighbor); // Get the coordinates of the neighbor
            if (neighborCoords) {
                std::cout << neighbor << " (" << neighborCoords->x << ", " << neighborCoords->y << ") ";
            }
        }
        std::cout << std::endl;
    }
*/
    std::vector<int> dijkstraNodeVisitOrder;
    std::vector<int> dijkstraPath = Algorithms::dijkstra(mazeGraph, 0, mazeGraph.GetIndexFromCoords(12, 4), dijkstraNodeVisitOrder);
    nodes.clear();
    history.clear();
    for(auto node : dijkstraPath)
    {
        nodes.push_back(mazeGraph.GetGraphNode(node));
    }
    for(auto node : dijkstraNodeVisitOrder)
    {
        history.push_back(mazeGraph.GetGraphNode(node));
    }

/*
    // Display the path in the terminal
    std::cout << "Dijkstra Path:" << std::endl;
    if (nodes.empty()) {
        std::cout << "No path found." << std::endl;
    } else {
        for (const auto& node : nodes) {
            std::cout << "(" << node->x << ", " << node->y << ") -> ";
        }
        std::cout << "End" << std::endl;
    }

    // Display the node visit order in the terminal
    std::cout << "Dijkstra Node Visit Order:" << std::endl;
    for (const auto& node : history) {
        std::cout << "(" << node->x << ", " << node->y << ") ";
    }
    std::cout << std::endl;
*/

    // Save Dijkstra path and visit order to text files
    WriteGraphNodesToTextFile("output/dijkstra_path.txt", nodes);
    WriteGraphNodesToTextFile("output/dijkstra_visit_order.txt", history);

    return 0;
}