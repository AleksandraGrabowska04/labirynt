#include <vector>
#include <set>
#include <stack>
#include "graph.h"

namespace Algorithms 
{
    void dfs(MazeGraph& mazeGraph, int startNode, int endNode, std::stack<int>& graphStack, std::vector<int>& nodeVisitOrder)
    {
        std::set<int> visited;
        graphStack.push(startNode);
        while(!graphStack.empty())
        {
            int currentNode = graphStack.top();
            graphStack.pop();
            if(currentNode == endNode)
            {
                visited.insert(currentNode);
                nodeVisitOrder.push_back(currentNode);
                break;
            }

            if(visited.find(currentNode) == visited.end())
            {
                visited.insert(currentNode);
                nodeVisitOrder.push_back(currentNode);
                std::vector<int> adjNodes = mazeGraph.GetAdjacentNodeIndicies(currentNode);
                for(auto it = adjNodes.begin(); it != adjNodes.end(); it++)
                {
                    if(visited.find(*it) == visited.end())
                    {
                        graphStack.push(*it);
                    }
                }
            }
        }
    }
}