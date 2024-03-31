#pragma once

#ifndef _SUDOKU_H_
#define _SUDOKU_H_

#include <vector>
#include <iostream>
#include "cell.h"
#include <sstream>

using std::vector;

class Sudoku 
{
private:
	std::vector<std::vector<Cell>> grid;
	size_t row;
	size_t col;

public:
	Sudoku(size_t r = 9, size_t c = 9) : row(r), col(c), grid(r, vector<Cell>(c)) {
		initRegions();
	}
	void initRegions();
	bool checkEnd();

	bool checkForPairs();
	bool setCandidates();
	bool singleFinder();

	bool checkLoners();

	void solve()
	{
		unsigned counter = 0;
		while (!checkEnd())
		{
			checkForPairs();

			std::cout << "Iteration number: " << counter++ << std::endl;
			singleFinder();
			print();
			
			std::cout << "Iteration number: " << counter++ << std::endl;
			checkLoners();
			print();
		}
	}

	void readIn(const std::string& s);
	void print() const;

};



#endif