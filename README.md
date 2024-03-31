# Sudoku Solver

## Introduction
This Sudoku Solver is a C++ project that demonstrates how to solve Sudoku puzzles using common solving techniques. It utilizes a `Cell` class to represent individual cells in the puzzle and a `Sudoku` class to handle the grid and solving logic.

## Features
- Load Sudoku puzzles from a string input.
- Solve puzzles using techniques like single candidates, hidden pairs, and region checks.
- Print the Sudoku grid to the console.

## How to Compile and Run
To compile and run this project, you need a C++ compiler that supports C++11 or later. Use the following steps:

1. Clone the repository to your local machine.
2. Navigate to the project directory.
3. Compile the code. For example, if you are using `g++`, you can compile the project with the following command:
    ```
    g++ -o sudoku main.cpp sudoku.cpp cell.cpp -std=c++11
    ```
4. Run the executable:
    ```
    ./sudoku
    ```

## Example Usage
Here's an example of how to use the Sudoku solver:

1. The `main` function in `main.cpp` initializes a `Sudoku` object with a default 9x9 grid.
2. It reads in a Sudoku puzzle from a string using the `readIn` method.
3. The `solve` method is called to solve the puzzle.
4. Finally, the solved Sudoku grid is printed to the console.

```cpp
#include "sudoku.h"
#include <iostream>

int main() {
    Sudoku s(9, 9);

    std::string puzzle =
        "0 0 0 1 2 3 0 0 0\n"
        "0 0 4 5 0 0 0 0 0\n"
        "0 2 3 0 0 0 0 0 0\n"
        "6 7 0 0 0 0 0 0 8\n"
        "8 0 0 0 0 0 0 0 4\n"
        "5 0 0 0 0 0 0 7 2\n"
        "0 0 0 0 0 0 1 8 0\n"
        "0 0 0 0 0 8 3 0 0\n"
        "0 0 0 6 4 9 0 0 0";

    s.readIn(puzzle);
    s.solve();
    s.print();

    return 0;
}
