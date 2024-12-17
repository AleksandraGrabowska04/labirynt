#pragma once
#include <stack>
#include <vector>
#include "graph.h"
#include "mazemap.h"

namespace Algorithms
{
    // accepts mazeGraph, startNode and endNode as inputs, 
    // returns the path from startNode to endNode, outNodeVisitOrder is a std::vector reference
    // and gets filled with all the nodes visited in the order they were visited
    std::vector<int> dfs(MazeGraph& mazeGraph, int startNode, int endNode,
        std::vector<int>& outNodeVisitOrder);

    // usage is the same as dfs, but uses breadth first search
    std::vector<int> bfs(MazeGraph& mazeGraph, int startNode, int endNode,
        std::vector<int>& outNodeVisitOrder);

    // Dijkstra's algorithm
    std::vector<int> dijkstra(MazeGraph& graph, int startNode, int endNode,
        std::vector<int>& outNodeVisitOrder);

    // A Star algorithm
    std::vector<int> a_star(MazeMap& lab, MazeGraph& graph, int startNode, int endNode,
        std::vector<int>& outNodeVisitOrder);
}