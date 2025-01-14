#include <gtest/gtest.h>
#include <mazemap.h>
#include <graph.h>
#include <filesystem>
#include "algorithms/algorithms.h"
#include "tests/helpers.h"

class AlgorithmsTest : public testing::Test {
protected:
    AlgorithmsTest() : map(resolvePath("test/data/maze_9x9.txt").c_str()), graph(map.ToMazeGraph())
    {
        mazeSize = map.GetMazeWidth();
    }

    int mazeSize;
    MazeMap map;
    MazeGraph graph;
};;

// #define RUN_ALGORITHM(algName, graphNodesVisitOrder) \
//     std::vector<int> nodeVisitOrder; \
//     algName(graph, 0, graph.GetIndexFromCoords(mazeSize - 2, mazeSize - 2), nodeVisitOrder); \
//     for(auto node : nodeVisitOrder) \
//         graphNodesVisitOrder.push_back(graph.GetGraphNode(node)); 

bool matchNodeVisitOrder(std::vector<std::shared_ptr<MazeGraphNode>> nodeVisitOrder, std::vector<std::pair<int, int>> expectedOrder)
{
    if(nodeVisitOrder.size() != expectedOrder.size())
        return false;
    for(int i = 0; i < nodeVisitOrder.size(); i++)
    {
        auto node = nodeVisitOrder[i];
        auto expectedNode = expectedOrder[i];
        if(node->x != expectedNode.first || node->y != expectedNode.second)
            return false;
    }
    return true;
}

TEST_F(AlgorithmsTest, DFS)
{
    std::vector<int> nodeVisitOrder;
    Algorithms::dfs(graph, 0, graph.GetIndexFromCoords(mazeSize - 2, mazeSize - 2), nodeVisitOrder);
    std::vector<std::shared_ptr<MazeGraphNode>> graphNodesVisitOrder;
    for(auto node : nodeVisitOrder)
    {
        graphNodesVisitOrder.push_back(graph.GetGraphNode(node));
    }

    std::vector<std::pair<int, int>> expectedOrder {
        {1, 1},
        {1, 2},
        {1, 3},
        {1, 4},
        {2, 4},
        {3, 4},
        {4, 4},
        {4, 5},
        {4, 6},
        {4, 7},
        {5, 7},
        {6, 7},
        {7, 7}
    };

    ASSERT_TRUE(matchNodeVisitOrder(graphNodesVisitOrder, expectedOrder));
}

TEST_F(AlgorithmsTest, BFS)
{
    std::vector<int> nodeVisitOrder;
    Algorithms::bfs(graph, 0, graph.GetIndexFromCoords(mazeSize - 2, mazeSize - 2), nodeVisitOrder);
    std::vector<std::shared_ptr<MazeGraphNode>> graphNodesVisitOrder;
    for(auto node : nodeVisitOrder)
    {
        graphNodesVisitOrder.push_back(graph.GetGraphNode(node));
    }
    std::vector<std::pair<int, int>> expectedOrder {
        {1, 1},
        {1, 2},
        {1, 3},
        {1, 4},
        {2, 4},
        {3, 4},
        {4, 4},
        {4, 5},
        {4, 6},
        {4, 7},
        {3, 7},
        {5, 7},
        {2, 7},
        {6, 7},
        {1, 7},
        {7, 7}
    };

    ASSERT_TRUE(matchNodeVisitOrder(graphNodesVisitOrder, expectedOrder));
}

TEST_F(AlgorithmsTest, Dijkstra)
{
    std::vector<int> nodeVisitOrder;
    Algorithms::dijkstra(graph, 0, graph.GetIndexFromCoords(mazeSize - 2, mazeSize - 2), nodeVisitOrder);
    std::vector<std::shared_ptr<MazeGraphNode>> graphNodesVisitOrder;
    for(auto node : nodeVisitOrder)
    {
        graphNodesVisitOrder.push_back(graph.GetGraphNode(node));
    }
    std::vector<std::pair<int, int>> expectedOrder {
        {1, 1},
        {1, 2},
        {1, 3},
        {1, 4},
        {2, 4},
        {3, 4},
        {4, 4},
        {4, 5},
        {4, 6},
        {4, 7},
        {3, 7},
        {5, 7},
        {2, 7},
        {6, 7},
        {1, 7},
        {7, 7}
    };

    ASSERT_TRUE(matchNodeVisitOrder(graphNodesVisitOrder, expectedOrder));
}

TEST_F(AlgorithmsTest, AStar) {
    std::vector<int> nodeVisitOrder;
    Algorithms::a_star(graph, 0, graph.GetIndexFromCoords(mazeSize - 2, mazeSize - 2), nodeVisitOrder);
    std::vector<std::shared_ptr<MazeGraphNode>> graphNodesVisitOrder;
    for(auto node : nodeVisitOrder)
    {
        graphNodesVisitOrder.push_back(graph.GetGraphNode(node));
    }
    std::vector<std::pair<int, int>> expectedOrder {
        {1, 1},
        {1, 2},
        {1, 3},
        {1, 4},
        {2, 4},
        {3, 4},
        {4, 4},
        {4, 5},
        {4, 6},
        {4, 7},
        {5, 7},
        {6, 7},
        {7, 7}
    };

    ASSERT_TRUE(matchNodeVisitOrder(graphNodesVisitOrder, expectedOrder));
}