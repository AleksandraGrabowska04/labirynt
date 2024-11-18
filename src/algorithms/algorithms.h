#pragma once
#include <stack>
#include <vector>
#include "graph.h"

namespace Algorithms
{
    // accepts mazeGraph, startNode and endNode as inputs, 
    // and outputs the path from startNode to endNode, as well as all the visited nodes in order
    void dfs(MazeGraph& mazeGraph, int startNode, int endNode,
        std::stack<int>& graphStack, std::vector<int>& nodeVisitOrder);
}