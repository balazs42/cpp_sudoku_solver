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

	void solve();

	void readIn(const std::string& s);
	void print() const;

	vector<Cell>& getRegionVector(const size_t& idx);
	Cell* getRegion(const size_t& idx);
	vector<Cell>& getRegionVector(const size_t& idx1, const size_t& idx2);
	Cell* getRegion(const size_t& idx1, const size_t& idx2);

	bool sameRow(const Cell& c1, const Cell& c2) const;
	bool sameCol(const Cell& c1, const Cell& c2) const;
	bool sameReg(const Cell& c1, const Cell& c2) const;
	bool same(const Cell& c1, const Cell& c2) const;
};
#endif