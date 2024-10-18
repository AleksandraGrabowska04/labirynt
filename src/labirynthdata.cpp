#include <iostream>
#include <vector>
#include <fstream>
#include <cstdint>

class Labirynth {
    std::vector<bool> lab;
    int rows, cols;

public:
    Labirynth(int rows, int cols) : rows(rows), cols(cols) 
    {
        lab.resize(rows * cols);
        for(int i = 0; i < rows*cols; i++) 
        {
            lab[i] = false;
        }
    }

    void MarkWall(int row, int col) 
    {
        lab[row * cols + col] = true;
    }

    void ClearWall(int row, int col) 
    {
        lab[row * cols + col] = false;
    }

    void Print()
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

    void ExportText(const char* filename) 
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

    void ExportBinary(const char* filename) 
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
};

int main()
{
    Labirynth lab(5, 5);
    lab.MarkWall(1, 1);
    lab.Print();
    lab.ExportBinary("lab.bin");
    return 0;
}