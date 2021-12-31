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

#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <sstream>
#include <thread>
#include <mutex>
#include <atomic>

using namespace std;

class SudokuGrid
{
private:
	string m_strGridName;						// the name of the grid, e.g. "Grid 01"
	unsigned char m_gridElement[9][9];			// to store the sudoku grid numbers in the 9x9 grid

	bool isPresentInCol(int col, int num);								// check if num is present in a given column of 9x9 grid
	bool isPresentInRow(int row, int num);								// check if num is present in a given row of 9x9 grid
	bool isPresentInBox(int boxStartRow, int boxStartCol, int num);		// check if num is present in a given box of 9x9 grid
	bool findEmptyPlace(int &row, int &col);							// determine if place is empty
	bool isValidPlace(int row, int col, int num);						// determine if place is valid for num

public:
	SudokuGrid()	// constructor
	{
		m_strGridName = "Grid 00";
		m_gridElement[9][9];
	}
	bool solve();		// solve() function starts off the solving of a SudokuGrid object, must be public, calls on all other private functions to solve
	void clear();		// clear() function can be used to clear a SudokuGrid object 
	friend fstream& operator>>(fstream& os, SudokuGrid& gridIn);			// used to read IN a SudokuGrid object FROM a text file
	friend fstream& operator<<(fstream& os, const SudokuGrid& gridIn);		// used to read OUT a SudokuGrid object TO a text file
};

