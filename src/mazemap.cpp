#include <iostream>
#include <vector>
#include <fstream>
#include <cstdint>
#include <stack>
#include <string>
#include <sstream>
#include <initializer_list>
#include "mazemap.h"
#include "graph.h"

MazeMap::MazeMap(int rows, int cols) : rows(rows), cols(cols) 
{
    lab.resize(rows * cols);
    for(int i = 0; i < rows*cols; i++) 
    {
        lab[i] = false;
    }
}

MazeMap::MazeMap(int rows, int cols, std::initializer_list<std::pair<int,int>> initializerList)
    : rows(rows), cols(cols) 
{
    lab.resize(rows * cols);
    for(int i = 0; i < rows*cols; i++) 
    {
        lab[i] = false;
    }
    for(auto it = initializerList.begin(); it != initializerList.end(); it++)
    {
        MarkWall(it->first, it->second);
    }
}

MazeMap::MazeMap(const char* filename)
{
    std::fstream file;
    file.open(filename, std::ios::in);
    if(!file.is_open())
    {
        std::cerr << "Could not open file: " << filename << std::endl;
        return;
    }
    rows = 1;
    cols = 0;
    std::string firstLine;
    std::getline(file, firstLine);
    std::stringstream ss(firstLine);
    for(char s : firstLine)
    {
        cols++;
    }
    std::string line;
    while(std::getline(file, line))
    {
        rows++;
    }
    file.close();

    lab.resize(rows * cols);
    for(int i = 0; i < rows*cols; i++) 
    {
        lab[i] = false;
    }
    ReadText(filename);
}

struct Position {
    int row;
    int col;
    bool operator=(const Position& pos) {
        return row == pos.row && col == pos.col;
    }
};

MazeGraph MazeMap::ToMazeGraph(int startPosRow, int startPosCol)
{
    const std::vector<std::pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    std::set<std::pair<int, int>> edges;
    std::stack<Position> posStack;
    std::stack<int> connectingIndexStack;
    Position startPos;
    startPos.row = startPosRow;
    startPos.col = startPosCol;
    MazeGraph graph(0);
    posStack.push(startPos);
    
    while(!posStack.empty()) 
    {
        Position pos = posStack.top();
        posStack.pop();
        int currIdx;
        currIdx = graph.GetIndexFromCoords(pos.row, pos.col);
        if(currIdx == -1) // can't find an existing index.. add a new vert
            currIdx = graph.AddVertex(pos.row, pos.col);
        int prevIdx = -1;
        if(!connectingIndexStack.empty())
        {
            prevIdx = connectingIndexStack.top();
            connectingIndexStack.pop();
            if(graph.EdgeExists(prevIdx, currIdx))
            {
                continue;
            }
            graph.AddEdge(prevIdx, currIdx);
        }

        for(auto dir : directions)
        {
            int newRow = pos.row + dir.first;
            int newCol = pos.col + dir.second;
            if(newRow < 0 || newRow >= rows || newCol < 0 || newCol >= cols)
                continue;
            if(Get(newRow, newCol) == true) // if the cell is a wall
                continue;
            posStack.push({newRow, newCol});
            connectingIndexStack.push(currIdx);
        }
    }
    return graph;
}

void MazeMap::MarkWall(int row, int col)
{
    lab[row * cols + col] = true;
}

void MazeMap::ClearWall(int row, int col) 
{
    lab[row * cols + col] = false;
}

void MazeMap::Print()
{
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            std::cout << (lab[i * cols + j] ? "1" : "0") << " ";
        }
        std::cout << std::endl;
    }
}

void MazeMap::ExportText(const char* filename) 
{
    std::fstream file;
    file.open(filename, std::ios::out);
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++)
        {
            file << (lab[i * cols + j] ? "1" : "0") << " ";
        }
        file << std::endl;
    }
}

void MazeMap::ReadText(const char* filename)
{
    std::fstream file;
    file.open(filename, std::ios::in);
    if(!file.is_open())
    {
        std::cerr << "Could not open file: " << filename << std::endl;
        return;
    }
    std::string line;
    int row = 0;
    while(std::getline(file, line))
    {
        std::stringstream ss(line);
        int col = 0;
        for(char s : line)
        {
            if(s == '1')
                MarkWall(row, col);
            col++;
        }
        row++;
    }
    file.close();
}

void MazeMap::ExportBinary(const char* filename) 
{
    std::fstream file;
    file.open(filename, std::ios::out | std::ios::binary);
    file.write((char*)&rows, sizeof(uint32_t));
    file.write((char*)&cols, sizeof(uint32_t));
    
    for (int i = 0; i < ((rows * cols) / 8) + 1; i++) // evaluate how many 8-bit integers we need
    {
        uint8_t byte = 0;
        for(int j=0; j<8; j++) // packing bits.
        {
            int index = i * 8 + j;
            if(index >= rows * cols) break;
            byte |= (lab[index] << j);
        }
        file.write((char*)&byte, sizeof(uint8_t));
    }
    file.close();
}

void MazeMap::ReadBinary(const char* filename)
{
    std::fstream file;
    file.open(filename, std::ios::in | std::ios::binary);
    file.read((char*)&rows, sizeof(uint32_t));
    file.read((char*)&cols, sizeof(uint32_t));
    lab.resize(rows * cols);
    for (int i = 0; i < ((rows * cols) / 8) + 1; i++) // evaluate how many 8-bit integers we need
    {
        uint8_t byte;
        file.read((char*)&byte, sizeof(uint8_t));
        for(int j=0; j<8; j++) // unpacking bits.
        {
            int index = i * 8 + j;
            if(index >= rows * cols) break;
            lab[index] = (byte >> j) & 1;
        }
    }

    file.close();
}

bool MazeMap::Get(int row, int col)
{
    return lab[row * cols + col];
}

void MazeMap::GetFullRow(int row, std::vector<bool>& row_data)
{
    row_data.resize(cols);
    for (int i = 0; i < cols; i++)
    {
        row_data[i] = lab[row * cols + i];
    }
}

void MazeMap::GetFullCol(int col, std::vector<bool>& col_data)
{
    col_data.resize(rows);
    for (int i = 0; i < rows; i++)
    {
        col_data[i] = lab[i * cols + col];
    }
}

void MazeMap::Clear()
{
    lab.clear();
}