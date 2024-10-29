#include "labirynthdata.h"
#include "graph.h"
#include <iostream>
int main()
{
    Labirynth lab(5, 5);
    // lab.MarkWall(1, 1);
    // lab.ExportBinary("lab.bin");
    // lab.Clear();
    // lab.Print();
    // std::vector <bool> row;
    // lab.GetFullRow(1, row);
    // for (int i = 0; i < row.size(); i++)
    // {
    //     std::cout << row[i] << " ";
    // }
    MazeGraph graph(3);
    int idx1 = graph.AddVertex(1, 1);
    int idx2 = graph.AddVertex(2, 2);
    int idx3 = graph.AddVertex(3, 3);
    graph.AddEdge(idx1, idx2);
    graph.AddEdge(idx1, idx3);
    graph.Print();
    return 0;
}