# ECE6122-Lab3-Problem1-SudokuSolver

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
    
    Example execution in command line:
    ~$  g++ .\*.cpp a.exe
    ~$  a.exe input_sudoku.txt
    ~$ cat Lab3Prob1.txt
    
    (--series of solved sudokus--)
