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
public:
	Cell() : val(-1), region(std::pair<unsigned, unsigned>(0, 0))
	{
		for (unsigned i = 0; i < 9; i++)
			candidates.push_back(true);
	}
	Cell(const std::pair<unsigned, unsigned>& p) : val(-1), region(std::pair<unsigned, unsigned>(p.first, p.second))
	{
		for (unsigned i = 0; i < 9; i++)
			candidates.push_back(true);
	}

	Cell(const int& i, const vector<bool>& c, const std::pair<unsigned, unsigned>& p) : val(i), candidates(c), region(std::pair<unsigned, unsigned>(p.first, p.second)) {}

	void setIdx(const bool& b, const unsigned& num) { candidates[num] = b; }
	bool getIdx(const unsigned& num) { return candidates[num]; }

	void setVal(const int& v) { val = v; }
	void setCandidates(const vector<bool>& c) { candidates = c; }
	void setRegion(const std::pair<unsigned, unsigned>& p) { region = p; }

	vector<bool>& getCandidates() { return candidates; }
	int getVal() const { return val; }
	std::pair<unsigned, unsigned> getRegion() const { return region; }

	bool operator==(const Cell& other) const
	{
		return val == other.val;
	}

	bool operator!=(const Cell& other) const
	{
		return !(*this == other);
	}

	// Assignment operator
	Cell& operator=(const Cell& other) {
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
	// Custom new operator
	static void* operator new(size_t size) {
		std::cout << "Allocating memory for a Cell object of size " << size << std::endl;
		void* ptr = malloc(size);
		if (!ptr) {
			throw std::bad_alloc(); // Ensure that failure to allocate memory is handled
		}
		return ptr;
	}

	// Custom delete operator
	static void operator delete(void* ptr) {
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
};