#include <vector>
#include <fstream>
#include "graph.h"
#include <filesystem>
// Write a vector of MazeGraphNode pointers to a file
// The file format is as follows:
// - 4 bytes: number of nodes
// - for each node:
//   - 4 bytes: x coordinate
//   - 4 bytes: y coordinate
// Returns true if the operation was successful, false otherwise
bool WriteGraphNodesToFile(std::filesystem::path, std::vector<std::shared_ptr<MazeGraphNode>> nodes);
bool WriteGraphNodesToTextFile(std::filesystem::path, std::vector<std::shared_ptr<MazeGraphNode>> nodes);