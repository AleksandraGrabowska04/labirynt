#include "mazemap.h"
#include "algorithms/algorithms.h"
#include <iostream>
#include <stack>
#include <vector>

int main()
{
    // 1 0 1
    // 0 0 0
    // 0 1 0
    MazeMap lab("D:\\Share\\labirynt\\maze.txt");
    // MazeGraph grph = lab.ToMazeGraph(0, 0);
    // grph.Print();
    //lab.ExportText("D:\\Share\\labirynt\\maze_out.txt");
    // MazeMap lab(3, 3);
    MazeMap map(2, 2);
    MazeGraph graph = map.ToMazeGraph(0, 0);
    graph.Print();
    // lab.MarkWall(0, 0);
    // lab.MarkWall(0, 2);
    // lab.MarkWall(2, 1);
    return 0;
}