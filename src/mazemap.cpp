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
    int rows = 1;
    int cols = 0;
    std::string firstLine;
    std::getline(file, firstLine);
    std::stringstream ss(firstLine);
    while(std::getline(ss, firstLine, ' '))
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
    int nodeIdx;
    bool operator=(const Position& pos) {
        return row == pos.row && col == pos.col;
    }
};

#define ADD_VERTEX_WITH_EDGE(graph, row, col, origIdx) \
    int idx = graph.AddVertex(row, col); \
    graph.AddEdge(origIdx, idx);

MazeGraph MazeMap::ToMazeGraph(int startPosRow = 1, int startPosCol = 1)
{
    std::set<uint64_t> visited; // this is uniquely identifying a position in the maze like a linear array would
    std::set<std::pair<int, int>> edges;
    std::stack<Position> posStack;
    Position startPos;
    startPos.row = startPosRow;
    startPos.col = startPosCol;
    MazeGraph graph(0);
    startPos.nodeIdx = graph.AddVertex(startPos.row, startPos.col);
    posStack.push(startPos);
    
    while(!posStack.empty()) {
        Position pos = posStack.top();
        posStack.pop();
        uint64_t combinedIndex = pos.row * cols + pos.col;
        // find available positions around this cell
        if(visited.find(combinedIndex) == visited.end())
        {
            visited.insert(combinedIndex);
            int row = pos.row;
            int col = pos.col;
            int currIdx = pos.nodeIdx;
            std::vector<Position> available;
            if(row > 0 && !Get(row - 1, col)) 
            {
                uint64_t vIdx = (row - 1) * cols + col;
                if(visited.find(vIdx) == visited.end())
                {
                    int idx = graph.AddVertex(row - 1, col);
                    graph.AddEdge(currIdx, idx);
                    edges.insert({currIdx, idx});
                    edges.insert({idx, currIdx});
                    posStack.push({row - 1, col, idx});
                }
                else if(edges.find({currIdx, graph.GetIndexFromCoords(row - 1, col)}) == edges.end())
                {
                    graph.AddEdge(currIdx, graph.GetIndexFromCoords(row - 1, col));
                    // node already visited, find existing vertex index and add edge, don't visit the node again
                    int idx = graph.GetIndexFromCoords(row - 1, col);
                    graph.AddEdge(currIdx, idx);
                }
            }
            if(row < rows - 1 && !Get(row + 1, col)) 
            {
                uint64_t vIdx = (row + 1) * cols + col;
                if(visited.find(vIdx) == visited.end())
                {
                    int idx = graph.AddVertex(row + 1, col);
                    graph.AddEdge(currIdx, idx);
                    edges.insert({currIdx, idx});
                    edges.insert({idx, currIdx});
                    posStack.push({row + 1, col, idx});
                }
                else if(edges.find({currIdx, graph.GetIndexFromCoords(row + 1, col)}) == edges.end())
                {
                    // node already visited, find existing vertex index and add edge, don't visit the node again
                    int idx = graph.GetIndexFromCoords(row + 1, col);
                    graph.AddEdge(currIdx, idx);
                }
            }
            if(col > 0 && !Get(row, col - 1)) 
            {
                uint64_t vIdx = row * cols + (col - 1);
                if(visited.find(vIdx) == visited.end())
                {
                    int idx = graph.AddVertex(row, col - 1);
                    graph.AddEdge(currIdx, idx);
                    edges.insert({currIdx, idx});
                    edges.insert({idx, currIdx});
                    posStack.push({row, col - 1, idx});
                }
                else if(edges.find({currIdx, graph.GetIndexFromCoords(row, col - 1)}) == edges.end())
                {
                    // node already visited, find existing vertex index and add edge, don't visit the node again
                    int idx = graph.GetIndexFromCoords(row, col - 1);
                    graph.AddEdge(currIdx, idx);
                }
            }
            if(col < cols - 1 && !Get(row, col + 1)) 
            {
                uint64_t vIdx = row * cols + (col + 1);
                if(visited.find(vIdx) == visited.end())
                {
                    int idx = graph.AddVertex(row, col + 1);
                    graph.AddEdge(currIdx, idx);
                    edges.insert({currIdx, idx});
                    edges.insert({idx, currIdx});
                    posStack.push({row, col + 1, idx});
                }
                else if(edges.find({currIdx, graph.GetIndexFromCoords(row, col + 1)}) == edges.end())
                {
                    // node already visited, find existing vertex index and add edge, don't visit the node again
                    int idx = graph.GetIndexFromCoords(row, col + 1);
                    graph.AddEdge(currIdx, idx);
                }
            }

            // for(auto it = available.begin(); it != available.end(); it++) 
            // {
            //     posStack.push(*it);
            // }
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
    std::string cols;
    std::getline(file, cols);
    this->cols = std::stoi(cols);
    this->rows = this->cols;
    std::string line;
    int row = 0;
    while(std::getline(file, line))
    {
        std::stringstream ss(line);
        int col = 0;
        while(std::getline(ss, line, ' '))
        {
            if(line == "1")
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