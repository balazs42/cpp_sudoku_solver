#include "sudoku.h"

bool Sudoku::checkEnd()
{
	for (unsigned i = 0; i < row; i++)
		for (unsigned j = 0; j < col; j++)
			for (unsigned k = 0; k < row; k++)
				if (grid[i][j].getCandidates()[k])
					return false;
	return true;
}

void Sudoku::initRegions()
{
	// Implementation of region initialization, assuming Cell class has setRegion method
	for (size_t i = 0; i < row; ++i) 
	{
		for (size_t j = 0; j < col; ++j) 
		{
			// Calculate region based on i, j if necessary
			grid[i][j].setRegion({ i / 3, j / 3 }); // Example region calculation
		}
	}
}

bool Sudoku::singleFinder()
{
	setCandidates();

	for(int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			Cell& cell = grid[i][j];
			
			if (cell.getNumberOfCandidates() == 1 && cell.getVal() == -1)
			{
				for (int k = 0; k < 9; k++)
				{
					if (cell.getCandidates()[k])
					{
						cell.setVal(k + 1);
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool Sudoku::setCandidates()
{
	bool set = false;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (grid[i][j].getVal() != -1)
			{
				set = true;
				Cell& cell = grid[i][j];
				unsigned currVal = cell.getVal() - 1;

				// Check rows and columns
				for (int k = 0; k < row; k++)
					if (k != i)
						grid[k][j].getCandidates()[currVal] = false;

				for (int k = 0; k < col; k++)
					if (k != j)
						grid[i][k].getCandidates()[currVal] = false;
				
				// Check regions
				for (unsigned k = 0; k < row; k++)
					for (unsigned l = 0; l < col; l++)
  						if (grid[k][l].getRegion() == cell.getRegion())
							grid[k][l].getCandidates()[currVal] = false;
			}
		}
	}
	return set;
}

void Sudoku::readIn(const std::string& input) {
	std::istringstream stream(input);
	int value;
	for (size_t i = 0; i < row; ++i) {
		for (size_t j = 0; j < col; ++j) {
			if (!(stream >> value) || value < 0 || value > 9) {
				throw std::invalid_argument("Invalid input: expected numbers between 0 and 9");
			}
			else if (value == 0)
				grid[i][j].setVal(-1);
			else grid[i][j].setVal(value);
		}
	}
}
void Sudoku::print() const 
{
	std::cout << "------|-------|------\n";
	for (size_t i = 0; i < row; ++i) 
	{
		if (i % 3 == 0 && i != 0) 
			std::cout << "------|-------|------\n";

		for (size_t j = 0; j < col; ++j) 
		{
			if (j % 3 == 0 && j != 0) 
				std::cout << "| ";
			
			int val = grid[i][j].getVal();
			if (val > 0) 
				std::cout << val << " ";
			else 
				std::cout << ". "; // Empty cell representation
			
		}
		std::cout << std::endl;
	}
	std::cout << "------|-------|------\n";
}

bool Sudoku::checkLoners()
{
	for (unsigned i = 0; i < row; i++)
	{
		for (unsigned j = 0; j < col; j++)
		{
			Cell& cell = grid[i][j];
			unsigned currVal = cell.getVal();
			bool bk = false;

			if (currVal == -1)
			{
				bk = false;
				for (unsigned k = 0; k < 9; k++)
				{
					if (cell.getCandidates()[k])
					{
						// Check column
						unsigned l = 0;
						for (; l < row; l++)
							if (l != i && grid[l][j].getCandidates()[k] && grid[l][j].getVal() == -1)
								break;
						if (l == row)
						{
							cell.setVal(k + 1);
							setCandidates();
							break;
						}

						// Check row
						for (l = 0; l < col; l++)
							if (l != j && grid[i][l].getCandidates()[k] && grid[i][l].getVal() == -1)
								break;

						if (l == col)
						{
							cell.setVal(k + 1);
							setCandidates();
							break;
						}

						bool ck = true;

						// Check region
						for (l = 0; (l < row) && ck; l++)
						{
							ck = true;
							for (unsigned m = 0; m < col; m++)
							{
								if ((i != l || j != m) && grid[l][m].getRegion() == cell.getRegion() && grid[l][m].getCandidates()[k])
								{
									ck = false;
									break;
								}
							}
						}

						if (ck)
						{
							cell.setVal(k + 1);
							setCandidates();
							break;
						}
					}

				}
			}
		}
	}

	return true;
}

bool Sudoku::checkForPairs()
{
	for (unsigned i = 0; i < row; i++)
	{
		for (unsigned j = 0; j < col; j++)
		{
			Cell& cell0 = grid[i][j];

			if (cell0.getVal() != -1)
				continue;

			for (unsigned k = 0; k < col; k++)
			{
				Cell& cell1 = grid[i][k];
				if (cell1.getVal() != -1)
					continue;

				if ((cell0 != cell1) && cell0.getCandidates() == cell1.getCandidates() && cell0.getNumberOfCandidates() == 2)
				{
					unsigned val1 = 9;
					unsigned val2 = 9;
					
					for (unsigned num = 0; num < 9; num++)
					{
						if (cell0.getCandidates()[num])
						{
							if (val1 == 9)
								val1 = num;
							else
								val2 = num;
						}
					}

					for (unsigned l = 0; l < col; l++)
					{
						if (l != j && l != k || grid[i][l].getVal() == -1)
						{
							grid[i][l].getCandidates()[val1] = false;
							grid[i][l].getCandidates()[val2] = false;

						}
					}
				}
			}
			
			for (unsigned k = 0; k < row; k++)
			{
				Cell& cell1 = grid[k][j];
				if (cell1.getVal() != -1)
					continue;

				if ((cell0 != cell1) && cell0.getCandidates() == cell1.getCandidates() && cell0.getNumberOfCandidates() == 2)
				{
					unsigned val1 = 9;
					unsigned val2 = 9;

					for (unsigned num = 0; num < 9; num++)
					{
						if (cell0.getCandidates()[num])
						{
							if (val1 == 9)
								val1 = num;
							else
								val2 = num;
						}
					}

					for (unsigned l = 0; l < col; l++)
					{
						if (l != i && l != k && grid[l][j].getVal() == -1)
						{
							grid[l][j].getCandidates()[val1] = false;
							grid[l][j].getCandidates()[val2] = false;
						}
					}
				}
			}

			for (unsigned k = 0; k < row; k++)
			{
				for (unsigned l = 0; l < col; l++)
				{
					Cell& cell1 = grid[k][l];

					if (cell1.getVal() != -1)
						continue;

					if ((cell0 != cell1) && cell0.getCandidates() == cell1.getCandidates() && cell0.getNumberOfCandidates() == 2 && cell0.getRegion() == cell1.getRegion())
					{
						unsigned val1 = 9;
						unsigned val2 = 9;

						for (unsigned num = 0; num < 9; num++)
						{
							if (cell0.getCandidates()[num])
							{
								if (val1 == 9)
									val1 = num;
								else
									val2 = num;
							}
						}

						for (unsigned m = 0; m < row; m++)
						{
							for (unsigned n = 0; n < col; n++)
							{
								if ((m != i || n != j) && (m != k || n != l) && grid[m][l].getRegion() == cell0.getRegion() && grid[m][n].getVal() == -1)
								{
									grid[m][n].getCandidates()[val1] = false;
									grid[m][n].getCandidates()[val2] = false;
								}
							}
						}
					}
				}
			}
		}
	}
	return true;
}

vector<Cell>& Sudoku::getRegionVector(const size_t& idx)
{
	vector<Cell> retVec;

	std::pair<unsigned, unsigned> reg;

	switch (idx)
	{
		case 0:
			reg = { 0, 0 };
			break;
		case 1:
			reg = { 0, 1 };
			break;
		case 2:
			reg = { 0, 2 };
			break;
		case 3:
			reg = { 1, 0 };
			break;
		case 4:
			reg = { 1, 1 };
			break;
		case 5:
			reg = { 1, 2 };
			break;
		case 6:
			reg = { 2, 0 };
			break;
		case 7:
			reg = { 2, 1 };
			break;
		case 8:
			reg = { 2, 2 };
			break;
		default:
			std::cerr << "Invalid region!\n";
			break;
	}

	for (unsigned i = 0; i < row; i++)
		for (unsigned j = 0; j < col; j++)
			if (grid[i][j].getRegion() == reg)
				retVec.push_back(grid[i][j]);
	return retVec;
}

Cell* Sudoku::getRegion(const size_t& idx)
{
	vector<Cell> tmp = getRegionVector(idx);
	Cell* cells = new Cell[tmp.size()];
	for (unsigned i = 0; i < tmp.size(); i++)
		cells[i] = tmp[i];
	return cells;
}

vector<Cell>& Sudoku::getRegionVector(const size_t& idx1, const size_t& idx2)
{
	vector<Cell> retVec;
	std::pair<unsigned, unsigned> reg = { idx1, idx2 };

	for (unsigned i = 0; i < row; i++)
		for (unsigned j = 0; j < col; j++)
			if (grid[i][j].getRegion() == reg)
				retVec.push_back(grid[i][j]);

	return retVec;
}

Cell* Sudoku::getRegion(const size_t& idx1, const size_t& idx2)
{
	vector<Cell> tmp = getRegionVector(idx1, idx2);
	Cell* cells = new Cell[tmp.size()];
	for (unsigned i = 0; i < tmp.size(); i++)
		cells[i] = tmp[i];
	return cells;
}

void Sudoku::solve()
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

bool Sudoku::sameRow(const Cell& c1, const Cell& c2) const
{
	return (c1.getRow() == c2.getRow());
}

bool Sudoku::sameCol(const Cell& c1, const Cell& c2) const
{
	return (c1.getCol() == c2.getCol());
}

bool Sudoku::sameReg(const Cell& c1, const Cell& c2) const
{
	return (c1.getReg() == c2.getReg());
}

bool Sudoku::same(const Cell& c1, const Cell& c2) const
{
	return (sameRow(c1, c2) && sameCol(c1, c2) && sameReg(c1, c2));
}

// Tuple in row or coll should set the whole row and col candidates to false