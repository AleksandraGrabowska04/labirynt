#include <gtest/gtest.h>
#include "serialize.h"
#include "helpers.h"
#include <filesystem>
namespace fs = std::filesystem;

TEST(SerializeTest, FormatResults)
{
    std::string expected = "DFS 16 9\n";
    std::string actual = FormatResults("DFS", 9, 16);
    ASSERT_EQ(expected, actual);
}

TEST(SerializeTest, ResultsToTextFile)
{
    const char* nam = std::tmpnam(nullptr);
    auto tempFile = fs::temp_directory_path() / nam;
    std::vector<std::pair<int, int>> pairs {
        {1, 1},
        {1, 2},
        {2, 2},
        {2, 3},
    };
    auto nodes = pairsToGraphNodes(pairs);
    WriteGraphNodesToTextFile(tempFile, nodes);
    std::ifstream file;
    file.open(tempFile, std::ios::in);
    EXPECT_TRUE(file.good()) << "File could not be opened";
    std::stringstream ss;
    int nodesCount;
    file >> nodesCount;
    EXPECT_EQ(nodesCount, 4) << "Invalid node count at the beginning of the file (or it's missing)";
    // iterate nodes, and check if they are the same as the ones we wrote
    for(int i = 0; i < nodesCount; i++)
    {
        int x, y;
        file >> x >> y;
        EXPECT_TRUE(x == nodes[i]->x && y == nodes[i]->y);
    }
    file.close();
    fs::remove(tempFile);
}
