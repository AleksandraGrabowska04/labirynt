#include <stdexcept>
#include <iostream>
#include "graph.h"
MazeGraph::MazeGraph(int V)
{
    numV = 0;
    adj.resize(V);
    indexedNodeData.resize(V);
    for(int i = 0; i < V; i++)
    {
        adj[i] = std::make_shared<std::set<int>>();
    }
}
int MazeGraph::AddVertex(int x = -1, int y = -1)
{
    std::shared_ptr<MazeGraphNode> node = std::make_shared<MazeGraphNode>();
    node->x = x;
    node->y = y;
    node->visited = false;
    indexedNodeData.push_back(node);
    return numV++;
}
void MazeGraph::AddEdge(int v, int w)
{
    if(v >= numV || w >= numV || v < 0 || w < 0)
        throw std::invalid_argument("Vertex index out of bounds");
    if(v == w)
        throw std::invalid_argument("Self loops are not allowed");
    if(adj[v]->find(w) != adj[v]->end())
        throw std::invalid_argument("Edge already exists");

    adj[v]->insert(w);
    adj[w]->insert(v);
    //numV++;
}
void MazeGraph::Print()
{
    for(int i = 0; i < numV; i++)
    {
        std::cout << "Vertex " << i << " is connected to: ";
        for(auto it = adj[i]->begin(); it != adj[i]->end(); it++)
        {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
}
std::set<std::shared_ptr<MazeGraphNode>> MazeGraph::GetAdjacentNodes(int v)
{
    std::set<std::shared_ptr<MazeGraphNode>> connectedNodes;
    if(v >= numV || v < 0)
    {
        throw std::invalid_argument("Vertex index out of bounds");
    }
    auto connectedVerts = adj[v];
    for(auto it = connectedVerts->begin(); it != connectedVerts->end(); it++)
    {
        connectedNodes.insert(indexedNodeData[*it]);
    }
    return connectedNodes;
}