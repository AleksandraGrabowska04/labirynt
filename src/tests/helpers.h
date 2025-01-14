#include <string>
#include <filesystem>
#include "graph.h"

inline std::string resolvePath(const std::string& filePath)
{
    // recurse along parent paths until specified file is found
    std::filesystem::path baseDir = std::filesystem::current_path();
    while (baseDir.has_parent_path())
    {
        std::filesystem::path combinedPath = baseDir / filePath;
        if (std::filesystem::exists(combinedPath))
        {
            return combinedPath.string();
        }
        baseDir = baseDir.parent_path();
    }
    throw std::runtime_error("File not found");
}

inline std::vector<std::shared_ptr<MazeGraphNode>> pairsToGraphNodes(const std::vector<std::pair<int, int>>& pairs)
{
    std::vector<std::shared_ptr<MazeGraphNode>> graphNodes;
    for(const auto& pair : pairs)
    {
        graphNodes.push_back(std::make_shared<MazeGraphNode>(MazeGraphNode{pair.first, pair.second}));
    }
    return graphNodes;
}