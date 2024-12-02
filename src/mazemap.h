#pragma once
#include <vector>
#include "graph.h"
class MazeMap {
    std::vector<bool> lab;
    int rows, cols;

public:
    // Create labirynth of size rows x cols
    MazeMap(int rows, int cols);
    MazeMap(int rows, int cols, std::initializer_list<std::pair<int, int>> initializerList);
    MazeMap(const char* filename);
    // Create a graph representation of the labirynth
    MazeGraph ToMazeGraph(int startPosRow = 1, int startPosCol = 1);
    // Mark wall at position (row, col) (sets bit to 1)
    void MarkWall(int row, int col);
    // Clear wall at position (row, col) (sets bit to 0)
    void ClearWall(int row, int col);
    // Print labirynth structure as 0's and 1's in rows and cols
    void Print();
    bool Get(int row, int col);
    void GetFullRow(int row, std::vector<bool>& row_data);
    void GetFullCol(int col, std::vector<bool>& col_data);
    // Export labirynth structure as text file
    // The text file is a grid of 0's and 1's
    void ExportText(const char* filename);
    // Export into a binary format
    void ExportBinary(const char* filename);
    void ReadBinary(const char* filename);
    void ReadText(const char* filename);
    void Clear();
};