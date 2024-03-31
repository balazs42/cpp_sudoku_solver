#include <iostream>
#include "sudoku.h"

int main(void)
{
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
        "0 0 0 6 4 9 0 0 0\n";

	s.readIn(puzzle);

	s.solve();

	s.print();

	return 0;
}