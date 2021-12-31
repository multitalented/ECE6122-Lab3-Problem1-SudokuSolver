/*
Author: Deanna Gierzak
Class: ECE 6122
Last Date Modified: 10/13/2020

Description:

	This SudokuGrid class is used in conjunction with the attached main.cpp program
		to solve a series of Sudokus that are input from a text file. The Sudokus
		are read in from a text file in a format like this:

Grid 01
003020600
900305001
001806400
008102900
700000008
006708200
002609500
800203009
005010300

	The first line is the name of the SudokuGrid object, and the following 9 lines are 
		read into the m_gridElements array to represent the 9x9 Sudoku grid. These
		member variables define the SudokuGrid object.

	The member functions defined here for SudokuGrid are used to then solve an 
		individual initialized SudokuGrid after being read in.
	
	Friend functions are defined and used for the reading
		and writing of each SudokuGrid object from and to text files, respectively.
*/

#include "SudokuGrid.h"

/////////////////////////////////////////////////////////////////////
// FUNCTION: SOLVE A SUDOKU GRID OBJECT
//	INPUT:	NONE
//	RETURN: BOOL
//*****************************************************************//
// This public function starts off the solving of an individual 
//	SudokuGrid object, and calls on other private member functions
//*****************************************************************//
bool SudokuGrid::solve() 
{
	int row, col;
	if (!findEmptyPlace(row, col))
		return true;								//when all places are filled
	for (int num = 1; num <= 9; num++)				//valid numbers are 1 - 9
	{ 
		if (isValidPlace(row, col, num))			//check validation, if yes, put the number in the grid
		{ 
			this->m_gridElement[row][col] = num;
			if (solve())							//recursively go for other rooms in the grid
				return true;
			this->m_gridElement[row][col] = 0;		//turn to unassigned space when conditions are not satisfied
		}
	}
	return false;
}
/////////////////////////////////////////////////////////////////////
// FUNCTION: CHECK IF NUMBER IS PRESENT IN A COLUMN
//	INPUT:	COLUMN AS INT, NUMBER TO CHECK AS INT
//	RETURN: BOOL
//*****************************************************************//
// Check if a number is present in a given column of the 9x9 grid
// where m_gridElement is the 9x9 grid of the SudokuGrid object
//*****************************************************************//
bool SudokuGrid::isPresentInCol(int col, int num) { //check whether num is present in col or not
	for (int row = 0; row < 9; row++)
		if (this->m_gridElement[row][col] == num)
			return true;
	return false;
}
///////////////////////////////////////////////////////////////////
// FUNCTION: CHECK IF NUMBER IS PRESENT IN A ROW
//	INPUT:	ROW AS INT, NUMBER TO CHECK AS INT
//	RETURN: BOOL
//***************************************************************//
// Check if a number is present in a given row of the 9x9 grid
// where m_gridElement is the 9x9 grid of the SudokuGrid object
//***************************************************************//
bool SudokuGrid::isPresentInRow(int row, int num) { //check whether num is present in row or not
	for (int col = 0; col < 9; col++)
		if (this->m_gridElement[row][col] == num)
			return true;
	return false;
}

//////////////////////////////////////////////////////////////////////////
// FUNCTION: CHECK IF NUMBER IS PRESENT IN A 3 X 3 BOX
//	INPUT:	BOX STARTING ROW, BOX STARTING COLUMN, NUMBER TO CHECK AS INT
//	RETURN: BOOL
//**********************************************************************//
// Check if a number is present in a given 3x3 box of the 9x9 grid
// where m_gridElement is the 9x9 grid of the SudokuGrid object
//**********************************************************************//
bool SudokuGrid::isPresentInBox(int boxStartRow, int boxStartCol, int num) {
	//check whether num is present in 3x3 box or not
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			if (this->m_gridElement[row + boxStartRow][col + boxStartCol] == num)
				return true;
	return false;
}
////////////////////////////////////////////////////////////////////
// FUNCTION: FIND AN EMPTY PLACE
//	INPUT:	ROW AS INT, COLUMN AS INT
//	RETURN: BOOL
//****************************************************************//
// Determines whether the checked (row, col) place is empty (= 0)
//****************************************************************//
bool SudokuGrid::findEmptyPlace(int &row, int &col) { //get empty location and update row and column
	for (row = 0; row < 9; row++)
		for (col = 0; col < 9; col++)
			if (this->m_gridElement[row][col] == 0) //marked with 0 is empty
				return true;
	return false;
}
///////////////////////////////////////////////////////////////////
// FUNCTION: CHECK IF POSITION IS A VALID PLACE FOR NUMBER
//	INPUT:	ROW AS INT, COLUMN AS INT, NUMBER TO CHECK AS INT
//	RETURN: BOOL
//***************************************************************//
// Determines whether checked (row, col) position for number is
//	a valid place for the number to go
//***************************************************************//
bool SudokuGrid::isValidPlace(int row, int col, int num) {
	//when item not found in col, row and current 3x3 box
	return !isPresentInRow(row, num) && !isPresentInCol(col, num) && !isPresentInBox(row - row % 3, col - col % 3, num);
}
////////////////////////////////////////////////////////////////
// FUNCTION: CLEAR THE SUDOKU GRID OBJECT
//	INPUT:	NONE
//	RETURN: NONE
//************************************************************//
// Clears the SudokuGrid 9x9 grid by setting all elements = 0
//************************************************************//
void SudokuGrid::clear()
{
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			this->m_gridElement[i][j] = '0' - 48;
		}
	}
}
/////////////////////////////////////////////////////////////
// FRIEND OPERATOR <<			 fstream >> SudokuGrid obj
//*********************************************************//
// Friend function, File stream operator to read in
// SudokuGrid object from a text file
//*********************************************************//
fstream& operator>>(fstream& os, SudokuGrid& gridIn)
{
	string dataline;
	getline(os, gridIn.m_strGridName);			// take the first line as the grid name in format: "Grid 00"

	// from Dr. Hurley's 10/8 lecture... I think mine was already working, but just in case not... check
	char dummy[2] = { 0,0 };

	for (int ii = 0; ii < 9; ++ii)
	{
		getline(os, dataline);

		for (int jj = 0; jj < 9; ++jj) 
		{
			dummy[0] = dataline[jj];
			gridIn.m_gridElement[ii][jj] = atoi(dummy); //dataline[jj]; // (unsigned char) (dataline[jj]);
		}
	}
	return os;	
}
/////////////////////////////////////////////////////////////
// FRIEND OPERATOR <<			 fstream << SudokuGrid obj
//*********************************************************//
// Friend function, File stream operator to output a
// SudokuGrid object and to a text file
//*********************************************************//
fstream& operator<<(fstream& os, const SudokuGrid& gridIn)
{
	os << gridIn.m_strGridName << endl;			// output the first line as the grid name in format: "Grid 00"

	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			os << gridIn.m_gridElement[i][j] - 0;
		}
		os << endl;
	}
	return os;
}