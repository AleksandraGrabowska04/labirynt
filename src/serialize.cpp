#include <fstream>
#include <vector>
#include "graph.h"

bool WriteGraphNodesToFile(const char* filename, std::vector<std::shared_ptr<MazeGraphNode>> nodes)
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

bool WriteGraphNodesToTextFile(const char* filename , std::vector<std::shared_ptr<MazeGraphNode>> nodes)
{
    std::fstream file;
    file.open(filename, std::ios::out);
    if(file.good() == false)
        return false;

    for(const auto &node : nodes)
    {
        if(!node)
            continue;
        file << node->x << " " << node->y << std::endl;
    }
    file.close();
    return true;
}