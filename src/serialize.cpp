#include <fstream>
#include <vector>
#include "graph.h"
#include <filesystem>

bool WriteGraphNodesToFile(std::filesystem::path filename, std::vector<std::shared_ptr<MazeGraphNode>> nodes)
{
    std::fstream file;
    file.open(filename, std::ios::out | std::ios::binary);
    if(file.good() == false)
        return false;

    uint32_t size = nodes.size();
    if(!file.write(reinterpret_cast<char*>(&size), sizeof(uint32_t))) return false;
    for(const auto &node : nodes)
    {
        if(!node)
            continue;
        uint32_t x = node->x;
        uint32_t y = node->y;
        if(!file.write(reinterpret_cast<char*>(&x), sizeof(uint32_t))) return false;
        if(!file.write(reinterpret_cast<char*>(&y), sizeof(uint32_t))) return false;
    }
    file.close();
    return true;
}

bool WriteGraphNodesToTextFile(std::filesystem::path filename, std::vector<std::shared_ptr<MazeGraphNode>> nodes)
{
    std::fstream file;
    file.open(filename, std::ios::out);
    if(file.good() == false)
        return false;

    file << nodes.size() << std::endl;
    for(const auto &node : nodes)
    {
        if(!node)
            continue;
        file << node->x << " " << node->y << std::endl;
    }
    file.close();
    return true;
}

std::string FormatResults(const std::string& algorithmName, int mazeSize, const std::vector<std::shared_ptr<MazeGraphNode>>& nodes)
{
    std::stringstream ss;
    ss << algorithmName << " " << nodes.size() << " " << mazeSize << std::endl;
    // for(const auto& node : nodes)
    // {
    //     ss << node->x << " " << node->y << std::endl;
    // }
    return ss.str();
}

bool WriteResultsToTextFile(std::filesystem::path filename, 
    const std::string& algorithmName, int mazeSize, std::vector<std::shared_ptr<MazeGraphNode>>& nodes)
{
    std::fstream file;
    file.open(filename, std::ios::out);
    if(file.good() == false)
        return false;
    
    file << FormatResults(algorithmName, mazeSize, nodes);
    file.close();
    return true;
}