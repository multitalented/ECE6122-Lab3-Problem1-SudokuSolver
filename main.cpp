/*
Author: Deanna Gierzak
Class: ECE 6122
Last Date Modified: 10/13/2020

Description:

	This program takes an input text file of unsolved Sudoku Grids with initial numbers and 
		assumed solvability.

	C++ Multi-threading is used to parallelize the computation of solving the sudoku grids.
		The number of threads of the running system is determined and then one less than
		this number of threads are spawned to call the solveSudokuPuzzles function.

	Mutex objects are used to lock and protect the reading in and out of Sudoku grids:
		one for when a thread needs to read a single Sudoku from the input text file to a 
		SudokuGrid object, and one for outputting a SudokuGrid object to the output text file.

	The final output is a text file of the solved sudoku grids in the order in which they
		were solved by the threads (these will vary in order).

Sudoku input text file format is as follows:

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
Grid 02
200080300
060070084
030500209
000105408
000000000
402706000
301007040
720040060
004010003
---etc---
*/

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
//#include <chrono>
#include <iomanip>
#include <stdio.h>

using namespace std;

mutex outFileMutex;		// mutex variable to protect the writing of the solved sudoku grids to the ouput file
mutex inFileMutex;		// mutex variable to protect the reading of the unsolved sudoku grids from the input file
fstream outFile;		// file object for the output file
fstream inFile;			// file object for the input file
//fstream executionTimeFile;

#include "SudokuGrid.h"

void solveSudokuPuzzles()
{
	SudokuGrid newSudoku;

	do
	{
		inFileMutex.lock();				// lock the inFile mutex for region of exclusivity, protects the reading of the sudoku object
		if (inFile.eof())
		{
			inFileMutex.unlock();		// if the end of file was reached, then unlock the mutex and break the loop
			break;
		}
		//newSudoku.clear();				// initialize the sudoku grid object, found to not be necessary, so commenting out for speed improvement
		inFile >> newSudoku;			// take in a new sudoku object from the input file of sudoku grids
		inFileMutex.unlock();			// unlock the inFile mutex to resume

		newSudoku.solve();				// call the SudokuGrid object's solve() function which starts the process of solving an individual sudoku grid

		outFileMutex.lock();			// lock the outFile mutex for region of exclusivity, protects the writing of the sudoku object
		outFile << newSudoku;			// output the solved sudoku to the output file
		outFileMutex.unlock();			// unlock the outFile mutex to resume
	} while (true);						// do-while loop runs until the end of file is reached, where a break ends the loop
}

int main(int argc, char* argv[])
{
	//double execTime;

	// Open inFile, the input file
	inFile.open(argv[1]);

	if (!inFile.is_open())							// if not open
	{
		cout << "Sudoku Input File Not Found";		// sudoku input file not found (user probably forgot to enter command line argument or no file in folder)
		return 1;
	}
	else
	{
		cout << argv[1] << " is open!";				// confirmed to have been found and to be open!
	}

	// open/create the output file
	outFile.open("Lab3Prob1.txt", fstream::out);

	// for debugging
	//solveSudokuPuzzles();
	// uncomment for the parallelized code

	unsigned int numThreads = std::thread::hardware_concurrency();			// determine the number of threads available
	unsigned int usedThreads = numThreads - 1;								// use one less than the maximum number of threads, to leave master thread

	vector<std::thread> workerThreads;					// vector to hold the working threads and send them off to solve

	//auto start = chrono::high_resolution_clock::now();

	// each thread is put into the working threads vector as it calls the solveSudokuPuzzles function
	for (int i = 0; i < usedThreads; ++i)
	{
		workerThreads.push_back(std::thread(solveSudokuPuzzles));			// each thread starts their reading, solving, and writing of Sudoku Puzzles!
	}

	for (int i = 0; i < usedThreads; ++i)
	{
		workerThreads[i].join();											// join the threads after all are finished
	}
	
	inFile.close();		// close the input sudoku file
	outFile.close();	// close the solved sudokus output file
	
	return 0;
	//auto stop = chrono::high_resolution_clock::now();
	//auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
	//execTime = double(duration.count()) / 1000000000;
	//executionTimeFile.open("ExecutionTime_Serial.txt", fstream::out);
	//executionTimeFile.open("ExecutionTime_Parallel.txt", fstream::out);
	//executionTimeFile << fixed << setprecision(15) << execTime;
}

// To get the value of duration use the count() 
// member function on the duration object 
//cout << duration.count() << endl;

// determine number of threads that can run concurrently = numThreads
// spawn #-1, spawnThreads = numThreads - 1
// make each solve sudoku
// open the input_sudoku file and read in sudoku grids
// start the parallel threading here
// declare a SudokuGrid object for 1 of 50 of the read-in sudoku grids from file

// TIPS:
// ALWAYS pass structures and classes by reference
// use voids as return type if not returning anything - don't always need to return something!
// use initialization list in constructors - ALWAYS use
// ALWAYS use +=, -=, *= operators whenever possible, (save a copy and assignment operation)
// Declare variables only in the scope they are needed
// Avoid repeated dynamic memory allocations. Try to reuse memory whenever possible
//		container classes...
//			-- try to initially size vector to largest size you think you need, for example
//		memory pool class


//int err = 0, count = 0;
//pthread_t tid;
//fstream os("input_sudoku.txt");
//outFile.open();


// use getline for first line
// for i = 0, < 9
/*
while (outFile >> character && gridData.size() <= 88) // while taking in characters from input file to num, delimited by space by default?
{
gridData.push_back(character);	// add the new char to the gridData input vector
}*/
//gridName = gridName.append(gridData[4]);

//	cout << gridName;

//string concat = gridElements[0][4] + gridElements[0][5];

//gridName.append(gridElements[0][4]);

/*
for (int i = 0; i < gridData.size(); ++i)
{
cout << gridData[i];
}
*/