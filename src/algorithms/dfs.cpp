#include <vector>
#include <set>
#include <stack>
#include "graph.h"
#include "algorithms.h"

std::vector<int> Algorithms::dfs(MazeGraph& mazeGraph, int startNode, int endNode, std::vector<int>& nodeVisitOrder)
{
    std::set<int> visited;
    std::stack<int> graphStack;
    std::stack<std::vector<int>> pathStack;
    //std::vector<int> bestPath;
    graphStack.push(startNode);
    pathStack.push(std::vector<int>{startNode});
    while(!graphStack.empty())
    {
        int currentNode = graphStack.top();
        graphStack.pop();
        std::vector<int> path = pathStack.top();
        pathStack.pop();
        
        if(currentNode == endNode)
        {
            visited.insert(currentNode);
            nodeVisitOrder.push_back(currentNode);
            return path;
        }

        if(visited.find(currentNode) == visited.end())
        {
            visited.insert(currentNode);
            nodeVisitOrder.push_back(currentNode);
            std::vector<int> adjNodes = mazeGraph.GetAdjacentNodeIndicies(currentNode);
            for(auto neighbor = adjNodes.begin(); neighbor != adjNodes.end(); neighbor++)
            {
                if(visited.find(*neighbor) == visited.end())
                {
                    graphStack.push(*neighbor);
                    std::vector<int> newPath = path;
                    newPath.push_back(*neighbor);
                    pathStack.push(newPath);
                }
            }
        }
    }
    return std::vector<int>();
}