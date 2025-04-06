#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Define the grid type as a vector of strings
using Grid = vector<string>;

// Function to print the current state of the grid with borders before and after
void printGrid(const Grid& grid) {
    string border(grid[0].size(), '|'); // Create a border with the same width as the grid
    cout << border << "\n";  // Top border
    for (const string& row : grid) {
        cout << row << "\n";  // Print each row of the grid
    }
    cout << border << "\n";  // Bottom border
}

// Function to count live neighbors of a given cell
int countNeighbors(const Grid& grid, int row, int col) {
    int count = 0;
    int height = grid.size();
    int width = grid[0].size();

    // Check all 8 surrounding cells
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (dr == 0 && dc == 0) continue; // Skip the cell itself
            int r = row + dr;
            int c = col + dc;
            if (r >= 0 && r < height && c >= 0 && c < width) {
                if (grid[r][c] == 'O') ++count;  // Count live neighbors
            }
        }
    }
    return count;
}

// Function to generate the next step (next generation) of the grid
Grid stepGrid(const Grid& grid) {
    int height = grid.size();
    int width = grid[0].size();
    Grid next = grid;  // Copy current grid to the next generation

    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            int neighbors = countNeighbors(grid, r, c);
            if (grid[r][c] == 'O') {
                // Underpopulation or overpopulation rules
                if (neighbors < 2 || neighbors > 3)
                    next[r][c] = '.';
            } else {
                // Reproduction rule
                if (neighbors == 3)
                    next[r][c] = 'O';
            }
        }
    }

    return next;
}

int main() {
    Grid grid;
    string line;

    // Step 1: Read the initial grid from input
    while (getline(cin, line)) {
        if (line == "x") break;  // End of grid input
        grid.push_back(line);  // Add each row of the grid
    }

    // Step 2: Process commands ('s' for step, 'p' for print)
    while (getline(cin, line)) {
        for (char ch : line) {
            if (ch == 's') {
                grid = stepGrid(grid);  // Advance one step
            } else if (ch == 'p') {
                printGrid(grid);  // Print current grid
            }
        }
    }

    return 0;
}
