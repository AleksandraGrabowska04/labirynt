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
    return 0;
}