#include "gtest/gtest.h"
#include "mazemap.h"

#define VEC_CONTAINS(vec, val) (std::find(vec.begin(), vec.end(), val) != vec.end())

TEST(MazeMapTest, AddWalls)
{
    MazeMap lab(3, 3);
    lab.MarkWall(0, 0);
    lab.MarkWall(0, 2);
    lab.MarkWall(2, 1);
    EXPECT_TRUE(lab.Get(0, 0));
    EXPECT_TRUE(lab.Get(0, 2));
    EXPECT_TRUE(lab.Get(2, 1));
    EXPECT_FALSE(lab.Get(2, 2));
}

TEST(MazeMapTest, AddAndClear)
{
    MazeMap lab(3, 3);
    lab.MarkWall(0, 0);
    lab.MarkWall(0, 2);
    lab.ClearWall(0, 2);
    EXPECT_FALSE(lab.Get(0, 2));
}

TEST(MazeMapTest, Initializer)
{
    MazeMap lab(3, 3, {{0, 0}, {0, 2}, {2, 1}});
    EXPECT_TRUE(lab.Get(0, 0));
    EXPECT_TRUE(lab.Get(0, 2));
    EXPECT_TRUE(lab.Get(2, 1));
    EXPECT_FALSE(lab.Get(2, 2));
}

TEST(MazeMapTest, MapToGraph_SimpleLoop)
{
    MazeMap lab(2, 2);
    MazeGraph graph = lab.ToMazeGraph();

    ASSERT_EQ(graph.GetNumVertices(), 4);

    auto adj0 = graph.GetAdjacentNodeIndicies(graph.GetIndexFromCoords(0, 0));
    // (0, 0) should be connected to (0, 1) and (1, 0)
    ASSERT_TRUE(VEC_CONTAINS(adj0, graph.GetIndexFromCoords(1, 0)));
    ASSERT_TRUE(VEC_CONTAINS(adj0, graph.GetIndexFromCoords(0, 1)));
    auto adj1 = graph.GetAdjacentNodeIndicies(graph.GetIndexFromCoords(1, 1));
    // (1, 1) should be connected to (0, 1) and (1, 0)
    ASSERT_TRUE(VEC_CONTAINS(adj1, graph.GetIndexFromCoords(1, 0)));
    ASSERT_TRUE(VEC_CONTAINS(adj1, graph.GetIndexFromCoords(0, 1)));
}

TEST(MazeMapTest, MapToGraph)
{
    MazeMap lab(3, 3, {{0, 0}, {0, 2}, {2, 1}, {2, 2}});
    MazeGraph graph = lab.ToMazeGraph();

    // (1, 1) should be connected to (0, 1), (1, 0) and (2, 1)
    auto adj2 = graph.GetAdjacentNodeIndicies(graph.GetIndexFromCoords(1, 1));
    ASSERT_TRUE(VEC_CONTAINS(adj2, graph.GetIndexFromCoords(1, 0)));
    ASSERT_TRUE(VEC_CONTAINS(adj2, graph.GetIndexFromCoords(0, 1)));
    ASSERT_TRUE(VEC_CONTAINS(adj2, graph.GetIndexFromCoords(1, 2)));
}

TEST(MazeGraphTest, AddVertex)
{
    MazeGraph graph(0);
    int idx = graph.AddVertex(1, 2);
    auto node = graph.GetGraphNode(idx);
    EXPECT_EQ(node->x, 1);
    EXPECT_EQ(node->y, 2);
}

TEST(MazeGraphTest, AddEdge)
{
    MazeGraph graph(0);
    int idx1 = graph.AddVertex(1, 2);
    int idx2 = graph.AddVertex(3, 4);
    graph.AddEdge(idx1, idx2);
    auto adj = graph.GetAdjacentNodeIndicies(idx1);
    EXPECT_EQ(adj.size(), 1);
    EXPECT_EQ(adj[0], idx2);
}

TEST(MazeGraphTest, GetIndexFromCoords)
{
    MazeGraph graph(0);
    int idx1 = graph.AddVertex(1, 2);
    ASSERT_EQ(graph.GetIndexFromCoords(1, 2), idx1);
}