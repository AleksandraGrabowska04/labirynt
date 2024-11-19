#include <stdexcept>
#include <iostream>
#include "graph.h"
MazeGraph::MazeGraph(int V)
{
    numV = 0;
    adj.resize(V);
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
    indexedNodeData.push_back(node);
    adj.push_back(std::make_shared<std::set<int>>());
    return numV++;
}
void MazeGraph::AddEdge(int v, int w)
{
    if(v >= numV || w >= numV || v < 0 || w < 0)
        throw std::invalid_argument("Vertex index out of bounds");
    if(v == w)
        throw std::invalid_argument("Self loops are not allowed");
    auto adjSet = adj.at(v);
    if(adjSet->find(w) != adjSet->end())
        throw std::invalid_argument("Edge already exists");

    adj[v]->insert(w);
    adj[w]->insert(v);
}
void MazeGraph::Print()
{
    for(int i = 0; i < numV; i++)
    {
        auto data = indexedNodeData[i];
        std::cout << "Vertex " << i << "(x: " << data->y << " y: " << data->x << ") is connected to: ";
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
std::vector<int> MazeGraph::GetAdjacentNodeIndicies(int v)
{
    std::vector<int> connectedNodes;
    if(v >= numV || v < 0)
    {
        throw std::invalid_argument("Vertex index out of bounds");
    }
    auto connectedVerts = adj[v];
    for(auto it = connectedVerts->begin(); it != connectedVerts->end(); it++)
    {
        connectedNodes.push_back(*it);
    }
    return connectedNodes;
}
std::shared_ptr<MazeGraphNode> MazeGraph::GetGraphNode(int v)
{
    if(v >= numV || v < 0)
    {
        throw std::invalid_argument("Vertex index out of bounds");
    }
    return indexedNodeData[v];
}
int MazeGraph::GetIndexFromCoordinates(int row, int col)
{
    for(int i = 0; i < numV; i++)
    {
        auto data = indexedNodeData[i];
        if(data->x == row && data->y == col)
        {
            return i;
        }
    }
    return -1;
}