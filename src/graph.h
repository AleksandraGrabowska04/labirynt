#pragma once
#include <vector>
#include <memory>
#include <set>

struct MazeGraphNode {
    int x;
    int y;
};
class MazeGraph {
    int numV;
    std::vector<std::shared_ptr<MazeGraphNode>> indexedNodeData;
    std::vector<std::shared_ptr<std::set<int>>> adj; 
public:
    MazeGraph(int V);
    int AddVertex(int x, int y);
    void AddEdge(int v, int w);
    void Print();
    int GetNumVertices() { return numV; }
    int GetIndexFromCoordinates(int row, int col);
    // Get the adjacent nodes of a vertex, as a set of pointers to MazeGraphNode
    std::set<std::shared_ptr<MazeGraphNode>> GetAdjacentNodes(int v);
    // Get the adjacent nodes of a vertex, as a vector of raw indices
    std::vector<int> GetAdjacentNodeIndicies(int v);
    std::shared_ptr<MazeGraphNode> GetGraphNode(int v);
    int GetIndexFromCoords(int x, int y);
    // order doesn't matter
    bool EdgeExists(int v, int w);
};