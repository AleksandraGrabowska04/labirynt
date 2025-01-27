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
std::string testAlgorithm(MazeGraph mazeGraph, int targetNode, std::vector<int> (*algo)(MazeGraph& mazeGraph, 
        int startNode, int endNode, std::vector<int>& outNodeVisitOrder), 
        std::filesystem::path fullDirPath, const char* visitOrderFileName, const char* fullPathFileName, 
        const char* algorithmName, int mazeSize){

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
    return FormatResults(algorithmName, mazeSize, graphNodesVisitOrder.size());
}

int main(int argc, char* argv[])
{
    std::stringstream resultsStream;

    const char* outputDir = "output";
    std::vector<int> mazeSizes;

    if(argc < 2){
        std::cout << "Usage: " << argv[0] << " <maze size numbers n (n x n, each divisible by 3, separated by space)> <[optional] output directory>" << std::endl;
        return 0;
    }
    for(int i = 1; i < argc; i++){

        if(strtol(argv[i], NULL, 10) > 0 && strtol(argv[i], NULL, 10) % 3 == 0){

            mazeSizes.push_back(strtol(argv[i], NULL, 10));

        }else if(strtol(argv[i], NULL, 10) == 0 && i >= 2){ //strtol conversion was invalid or returned 0 and at least one of the previous arguments was indeed proper maze size n number.

            outputDir = argv[i];
            break;

        }else{
            std::cout << "Passed improper program argument!!!" << std::endl;
            std::cout << "Maze size number was not given or invalid" << std::endl; //invalid i.e: either negative or zero number.
            std::cout << "Usage: " << argv[0] << " <maze size numbers n (n x n, each divisible by 3, separated by space)> <[optional] output directory>" << std::endl;
            return 1;
        }

    }
    
    std::filesystem::path fullDirPath = outputDir;
    std::filesystem::create_directories(fullDirPath);
    std::filesystem::path mazePath = fullDirPath / "maze.txt";
    std::string fullPathStr = mazePath.string();
    const char* mazePathStr = fullPathStr.c_str();

    for(int mazeSize : mazeSizes){

        //Randomly generating the new maze.
        create_maze(mazePathStr, mazeSize, mazeSize);
        //Storing a maze inside the custom data structure (reading and converting from generated labyrinth's matrix given in raw txt data).
        MazeMap mazeMap(mazePathStr);
        //Transfoming maze to a graph form.
        MazeGraph mazeGraph = mazeMap.ToMazeGraph();

        int targetNode = mazeSize - 2;

        // dfs
        resultsStream << testAlgorithm(mazeGraph, targetNode, Algorithms::dfs, fullDirPath,
                    "dfs_visit_order.txt", "dfs_path.txt", "DFS", mazeSize);

        // bfs
        resultsStream << testAlgorithm(mazeGraph, targetNode, Algorithms::bfs, fullDirPath,
                    "bfs_visit_order.txt", "bfs_path.txt", "BFS", mazeSize);

        // Dijkstra
        resultsStream << testAlgorithm(mazeGraph, targetNode, Algorithms::dijkstra, fullDirPath,
                    "dijkstra_visit_order.txt", "dijkstra_path.txt", "Dijkstra", mazeSize);

        // A star
        resultsStream << testAlgorithm(mazeGraph, targetNode, Algorithms::a_star, fullDirPath,
                    "a_star_visit_order.txt", "a_star_path.txt", "A*", mazeSize);

        std::fstream file;
        file.open(fullDirPath / "results.txt", std::ios::out);
        if(file.good() == false)
        {
            std::cerr << "Could not write to file: " << fullDirPath / "results.txt" << std::endl;
            return 1;
        }
        file << resultsStream.str();
        file.close();
    }
    return 0;
}