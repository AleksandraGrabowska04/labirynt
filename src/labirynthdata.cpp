#include <iostream>
#include <vector>
#include <fstream>
#include <cstdint>
#include <stack>
#include "labirynthdata.h"
#include "graph.h"

Labirynth::Labirynth(int rows, int cols) : rows(rows), cols(cols) 
{
    lab.resize(rows * cols);
    for(int i = 0; i < rows*cols; i++) 
    {
        lab[i] = false;
    }
}

struct Position {
    int row;
    int col;
    bool operator=(const Position& pos) {
        return row == pos.row && col == pos.col;
    }
};

#define ADD_VERTEX_WITH_EDGE(graph, row, col, origIdx) \
    int idx = graph.AddVertex(row, col); \
    graph.AddEdge(origIdx, idx);

MazeGraph Labirynth::ToMazeGraph()
{
    std::set<uint64_t> visited; // this is uniquely identifying a position in the maze like a linear array would
    std::stack<Position> posStack;
    Position startPos;
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            if(!lab[i * cols + j])
            {
                startPos.row = i;
                startPos.col = j;
                break;
            }
        }
    }
    MazeGraph graph(rows * cols);
    posStack.push(startPos);
    graph.AddVertex(startPos.row, startPos.col);
    
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
            int currIdx = graph.AddVertex(row, col);
            std::vector<Position> available;
            if(row > 0 && !Get(row - 1, col)) 
            {
                available.push_back({row - 1, col});
                ADD_VERTEX_WITH_EDGE(graph, row - 1, col, currIdx);
            }
            if(row < rows - 1 && !Get(row + 1, col)) 
            {
                available.push_back({row + 1, col});
                ADD_VERTEX_WITH_EDGE(graph, row + 1, col, currIdx);
            }
            if(col > 0 && !Get(row, col - 1)) 
            {
                available.push_back({row, col - 1});
                ADD_VERTEX_WITH_EDGE(graph, row, col - 1, currIdx);
            }
            if(col < cols - 1 && !Get(row, col + 1)) 
            {
                available.push_back({row, col + 1});
                ADD_VERTEX_WITH_EDGE(graph, row, col + 1, currIdx);
            }

            for(auto it = available.begin(); it != available.end(); it++) 
            {
                posStack.push(*it);
            }
        }
    }
    return graph;
}

void Labirynth::MarkWall(int row, int col) 
{
    lab[row * cols + col] = true;
}

void Labirynth::ClearWall(int row, int col) 
{
    lab[row * cols + col] = false;
}

void Labirynth::Print()
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

void Labirynth::ExportText(const char* filename) 
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

void Labirynth::ExportBinary(const char* filename) 
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

void Labirynth::ReadBinary(const char* filename)
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

bool Labirynth::Get(int row, int col)
{
    return lab[row * cols + col];
}

void Labirynth::GetFullRow(int row, std::vector<bool>& row_data)
{
    row_data.resize(cols);
    for (int i = 0; i < cols; i++)
    {
        row_data[i] = lab[row * cols + i];
    }
}

void Labirynth::GetFullCol(int col, std::vector<bool>& col_data)
{
    col_data.resize(rows);
    for (int i = 0; i < rows; i++)
    {
        col_data[i] = lab[i * cols + col];
    }
}

void Labirynth::Clear()
{
    lab.clear();
}