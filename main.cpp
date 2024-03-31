#include <iostream>
#include "sudoku.h"

int main(void)
{
	Sudoku s(9, 9);

    std::string puzzle =
        "0 6 0 0 4 0 8 0 0\n"
        "8 0 0 7 2 0 3 0 9\n"
        "4 0 0 0 0 0 0 0 6\n"
        "7 0 0 1 0 0 0 9 0\n"
        "0 0 8 0 7 0 0 0 2\n"
        "0 9 0 5 0 0 0 0 4\n"
        "0 0 6 0 0 0 0 0 0\n"
        "0 0 4 0 0 7 0 1 5\n"
        "1 0 9 2 0 4 6 8 0\n";

	s.readIn(puzzle);

	s.solve();

	s.print();

	return 0;
}