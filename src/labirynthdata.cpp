#include <iostream>
#include <vector>
#include <fstream>
#include <cstdint>
#include "labirynthdata.h"

Labirynth::Labirynth(int rows, int cols) : rows(rows), cols(cols) 
{
    lab.resize(rows * cols);
    for(int i = 0; i < rows*cols; i++) 
    {
        lab[i] = false;
    }
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

void Labirynth::Clear()
{
    lab.clear();
}