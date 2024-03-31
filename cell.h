#pragma once

#include <vector>
#include <iostream>
using std::vector;

class Cell
{
private:
	int val;
	std::pair<unsigned, unsigned> region;
	vector<bool> candidates;

	unsigned rowPos;
	unsigned colPos;
	unsigned regPos;

public:
	Cell() : val(-1), region(std::pair<unsigned, unsigned>(0, 0)), rowPos(0), colPos(0), regPos(0)
	{
		for (unsigned i = 0; i < 9; i++)
			candidates.push_back(true);
	}
	Cell(const std::pair<unsigned, unsigned>& p) : val(-1), region(std::pair<unsigned, unsigned>(p.first, p.second))
	{
		for (unsigned i = 0; i < 9; i++)
			candidates.push_back(true);

		rowPos = p.first;
		colPos = p.second;
		regPos = getRegionSingle();
	}

	Cell(const int& i, const vector<bool>& c, const std::pair<unsigned, unsigned>& p) : val(i), candidates(c), region(std::pair<unsigned, unsigned>(p.first, p.second)) {}

	void setIdx(const bool& b, const unsigned& num) { candidates[num] = b; }
	bool getIdx(const unsigned& num) { return candidates[num]; }

	void setVal(const int& v) { val = v; }
	void setCandidates(const vector<bool>& c) { candidates = c; }
	void setRegion(const std::pair<unsigned, unsigned>& p) { region = p; }
	void setRow(const unsigned& param) { rowPos = param; }
	void setCol(const unsigned& param) { colPos = param; }
	void setReg(const unsigned& param) { regPos = param; }

	vector<bool>& getCandidates() { return candidates; }
	int getVal() const { return val; }
	std::pair<unsigned, unsigned> getRegion() const { return region; }
	unsigned getRow() const { return rowPos; }
	unsigned getCol() const { return colPos; }
	unsigned getReg() const { return regPos; }

	bool operator==(const Cell& other) const
	{
		return val == other.val;
	}
	bool operator!=(const Cell& other) const
	{
		return !(*this == other);
	}
	Cell& operator=(const Cell& other)// Assignment operator
	{
		// Self-assignment check
		if (this == &other) {
			return *this;
		}

		// Copy each field from the other Cell object
		val = other.val;
		candidates = other.candidates;
		region = other.region;

		return *this; // Return a reference to the current object
	}
	static void* operator new(size_t size) // Custom new operator
	{
		std::cout << "Allocating memory for a Cell object of size " << size << std::endl;
		void* ptr = malloc(size);
		if (!ptr) {
			throw std::bad_alloc(); // Ensure that failure to allocate memory is handled
		}
		return ptr;
	}
	static void operator delete(void* ptr) 	// Custom delete operator
	{
		std::cout << "Deallocating memory for a Cell object" << std::endl;
		free(ptr);
	}

	int getNumberOfCandidates()
	{
		int counter = 0;
		for (int i = 0; i < 9; i++)
			if (candidates[i])
				counter++;

		return counter;
	}
	unsigned getRegionSingle()
	{
		if (region == std::pair<unsigned, unsigned>{0, 0})
			return 0;
		if (region == std::pair<unsigned, unsigned>{0, 1})
			return 1;
		if (region == std::pair<unsigned, unsigned>{0, 2})
			return 2;
		if (region == std::pair<unsigned, unsigned>{1, 0})
			return 3;
		if (region == std::pair<unsigned, unsigned>{1, 1})
			return 4;
		if (region == std::pair<unsigned, unsigned>{1, 2})
			return 5;
		if (region == std::pair<unsigned, unsigned>{2, 0})
			return 6;
		if (region == std::pair<unsigned, unsigned>{2, 1})
			return 7;
		if (region == std::pair<unsigned, unsigned>{2, 2})
			return 8;
	}
};