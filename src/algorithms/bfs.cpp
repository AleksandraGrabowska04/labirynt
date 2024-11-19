#include <vector>
#include <set>
#include <queue>
#include "graph.h"
#include "algorithms.h"

std::vector<int> Algorithms::bfs(MazeGraph& mazeGraph, int startNode, int endNode, std::vector<int>& nodeVisitOrder)
{
    std::set<int> visited;
    std::queue<int> graphQueue;
    // this queue will save each new path taken in the graph as a vector
    // when we get to the end we can return the path from the front of the queue
    std::queue<std::vector<int>> pathQueue;
    graphQueue.push(startNode);
    pathQueue.push(std::vector<int>{startNode});
    while(!graphQueue.empty())
    {
        int currentNode = graphQueue.front();
        graphQueue.pop();
        std::vector<int> path = pathQueue.front();
        pathQueue.pop();
        
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
                    graphQueue.push(*neighbor);
                    std::vector<int> newPath = path;
                    newPath.push_back(*neighbor);
                    pathQueue.push(newPath);
                }
            }
        }
    }
    return std::vector<int>();
}