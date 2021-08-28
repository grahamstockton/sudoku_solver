# sudoku_solver
Sudoku solver using recursive backtracking

This project takes in a sudoku problem as a text file and solves it for you. It will solve the problem,
tell you if there are errors in the starting problem, or tell you that there are no solutions

Backtracking structure
  This program implements a class with a std::vector<std::vector<char>> to represent the problem
  Changes are made in place to the array in a recursive fashion
  The solver progresses through the array, changing the current empty position to a value and checking if it is valid
     if it is, it calls itself on the next position
        if the end is reached, it will complete its run
  if at any point this process fails, it will erase the value and go back to the next previous valid position
  if the end is reached without any solution found, we know that there is no solution

Testing
  The solver includes a function tests(), which runs tests against 35 sudoku problems obtained from http://lipas.uwasa.fi/~timan/sudoku/
  It also tests against a number of sudoku problems without solutions, as well as problems that are invalid from the start (have two of a number in a row to begin with, for example)
  
Input file format
  The sudoku problem is read in from a std::ifstream. Any common representation that uses 0-9 chars separated by whitespace, with some other non-(0-9), non-whitespace char to represent blanks will work
