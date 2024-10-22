#include <vector>
class Labirynth {
    std::vector<bool> lab;
    int rows, cols;

public:
    // Create labirynth of size rows x cols
    Labirynth(int rows, int cols);
    // Mark wall at position (row, col) (sets bit to 1)
    void MarkWall(int row, int col);
    // Clear wall at position (row, col) (sets bit to 0)
    void ClearWall(int row, int col);
    // Print labirynth structure as 0's and 1's in rows and cols
    void Print();
    // Export labirynth structure as text file
    // The text file is a grid of 0's and 1's
    void ExportText(const char* filename);
    // Export into a binary format
    void ExportBinary(const char* filename);
    void ReadBinary(const char* filename);
    void Clear();
};