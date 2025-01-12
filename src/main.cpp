#include "mazemap.h"
#include <iostream>
#include <fstream>
#include "algorithms/algorithms.h"
#include <filesystem>
#include "serialize.h"

extern "C" int create_maze(const char* file_name, int maze_height, int maze_width);

bool isFileValid(const char *fileName)
{
    std::ifstream f(fileName);
    return f.good();
}

//Tests the given algorithm's maze/labyrinth solving and writes its results to the text files.
void testAlgorithm(MazeGraph mazeGraph, int targetNode, std::vector<int> (*algo)(MazeGraph& mazeGraph, 
        int startNode, int endNode, std::vector<int>& outNodeVisitOrder), 
        std::filesystem::path fullDirPath, const char* visitOrderFileName, const char* fullPathFileName){

    std::vector<int> nodeVisitOrder; //full history (order) of node visited.
    std::vector<int> fullNodePath; //full *solved* maze path.

    fullNodePath = algo(mazeGraph, 0, mazeGraph.GetIndexFromCoords(targetNode, targetNode), nodeVisitOrder);

    std::vector<std::shared_ptr<MazeGraphNode>> graphNodesVisitOrder; //names are self-explanatory (converting nodeVisitOrder and fullNodePath to their counterparts in actual maze nodes (MazeGraphNode's)). 
    std::vector<std::shared_ptr<MazeGraphNode>> fullgraphNodePath;

    for(auto node : nodeVisitOrder)
    {
        graphNodesVisitOrder.push_back(mazeGraph.GetGraphNode(node));
    }
    for(auto node : fullNodePath)
    {
        fullgraphNodePath.push_back(mazeGraph.GetGraphNode(node));
    }

    //Saving the algorithm results to the text files (algorithm which has been run on a maze/run for maze solution/solving).
    WriteGraphNodesToTextFile(fullDirPath / visitOrderFileName, graphNodesVisitOrder);
    WriteGraphNodesToTextFile(fullDirPath / fullPathFileName, fullgraphNodePath);

}

int main(int argc, char* argv[])
{

    const char* outputDir;
    if(argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <maze n size (n x n, divisible by 3)> <[optional] output dir>" << std::endl;
        return 0;
        
    }else if(argc == 2){
        outputDir = "output";
    }else{
        outputDir = argv[2];
    }
    int mazeSize = atoi(argv[1]);
    if(mazeSize < 3)
    {
        std::cout << "Maze size must be at least 3" << std::endl;
        return 1;
    }
    std::filesystem::path fullDirPath = outputDir;
    std::filesystem::create_directories(fullDirPath);
    std::filesystem::path mazePath = fullDirPath / "maze.txt";
    std::string fullPathStr = mazePath.string();
    const char* mazePathStr = fullPathStr.c_str();

    //Randomly generating the new maze.
    create_maze(mazePathStr, mazeSize, mazeSize);
    //Storing a maze inside the custom data structure (reading and converting from generated labyrinth's matrix given in raw txt data).
    MazeMap mazeMap(mazePathStr);
    //Transfoming maze to a graph form.
    MazeGraph mazeGraph = mazeMap.ToMazeGraph();

    int targetNode = mazeSize - 2;

    // dfs
    testAlgorithm(mazeGraph, targetNode, Algorithms::dfs, fullDirPath,
                 "dfs_visit_order.txt", "dfs_path.txt");

    // bfs
    testAlgorithm(mazeGraph, targetNode, Algorithms::bfs, fullDirPath,
                 "bfs_visit_order.txt", "bfs_path.txt");

    // Dijkstra
    testAlgorithm(mazeGraph, targetNode, Algorithms::dijkstra, fullDirPath,
                 "dijkstra_visit_order.txt", "dijkstra_path.txt");

    // A star
    testAlgorithm(mazeGraph, targetNode, Algorithms::a_star, fullDirPath,
                 "a_star_visit_order.txt", "a_star_path.txt");

    return 0;
}