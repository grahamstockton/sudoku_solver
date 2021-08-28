#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

/*
This project is a simple sudoku solver that implements recursive backtracking.
The input format is a file, sudoku.in, of 81 characters corresponding to a sudoku board (read LRTB).
It is on the user to make sure that the input file is formatted correctly, but our program will check if the sudoku problem itself is valid and solvable
The spaces on the input should be separated by whitespace
*/


class sudokuSolver
{
public:
    std::vector<std::vector<char>> problem;
    sudokuSolver(std::vector<std::vector<char>>& p) : problem(p) {}

    // returns true if solution found, else false
    bool solve(const int row = 0, const int col = 0) 
    {
        // get the next position, unpack
        std::tuple<int, int> pos = getNextSpot(row, col);
        int newRow = std::get<0>(pos), newCol = std::get<1>(pos);

        // check if we are at the end, otherwise recurse
        if (std::get<0>(pos) == -1) { 
            return true;
        } else {
            for (char a = '1'; a <= '9'; a++) {
                // change in place, check if valid, wipe if not valid. If valid, call on next spot
                problem[newRow][newCol] = a;
                if (checkPosition(newRow, newCol)) {
                    if (solve(newRow, newCol)) { return true; }
                } else {
                    problem[newRow][newCol] = '.';
                }
            }
            // nothing found
            return false;
        }
    }

    // checks entire board, using a bitmask
    bool checkBoard() {
        int rows, cols, box, value, boxRow, boxCol;
        for (int i = 0; i < 9; i++)
        {
            rows = 0, cols = 0, box = 0;
            for (int j = 0; j < 9; j++)
            {
                // check box, row, and column
                boxRow = 3*(i/3) + j/3;
                boxCol = 3*(i%3) + j%3;
                if ('1' <= problem[boxRow][boxCol]) {
                    value = 1 << (problem[boxRow][boxCol] - '0');
                    if (value & box) { return false; }
                    box |= value;
                }
                if ('1' <= problem[i][j] && problem[i][j] <= '9') {
                    value = 1 << (problem[i][j] - '0');
                    if (value & rows) { return false; }
                    rows |= value;
                }
                if ('1' <= problem[j][i] && problem[j][i] <= '9') {
                    value = 1 << (problem[j][i] - '0');
                    if (value & cols) { return false; }
                    cols |= value;
                }
            }
        }
        return true;
    }

private:
    // get the next empty spot on the board (LRTB)
    std::tuple<int, int> getNextSpot(int row, int col)
    {
        while (!(row == 9))
        {
            // if spot is empty return indices
            if (!('1' <= problem[row][col] && problem[row][col] <= '9')) {
                return {row, col};
            }

            // to go new row if at end, else move col
            if (col == 8) {
                col = 0;
                row++;
            } else {
                col++;
            }
        }

        // done.
        return {-1, -1};
    }

    // checks only the row, col, box containing problem[row][col]
    bool checkPosition(const int row, const int col)
    {
        const char ch = problem[row][col];
        int rowCount = 0, colCount = 0, boxCount = 0;
        for (int i = 0; i < 9; i++)
        {
            // check row, col, box
            if (problem[row][i] == ch) {
                colCount++;
            } 
            if (problem[i][col] == ch) {
                rowCount++;
            }
            if (problem[3*(row/3) + i/3][3*(col/3) + i%3] == ch) {
                boxCount++;
            }

            // check if too many values
            if (rowCount > 1 || colCount > 1 || boxCount > 1) {
                return false;
            }
        }

        return true;
    }

    void print(std::vector<std::vector<char>> &sudoku)
    {
        // row loop
        for (int i = 0; i < 9; i++)
        {
            // vertical spacing for boxes
            if (i % 3 == 0)
            {
                std::cout << std::endl;
            }

            // column loop
            for (int j = 0; j < 9; j++)
            {
                // horizontal spacing for boxes
                if (j % 3 == 0)
                {
                    std::cout << "  ";
                }
                // print item and space
                std::cout << sudoku[i][j] << "  ";
            }
            // end of line
            std::cout << std::endl << std::endl;
        }
    }
};

void print(std::vector<std::vector<char>> &sudoku)
{
    // row loop
    for (int i = 0; i < 9; i++)
    {
        // vertical spacing for boxes
        if (i % 3 == 0)
        {
            std::cout << std::endl;
        }

        // column loop
        for (int j = 0; j < 9; j++)
        {
            // horizontal spacing for boxes
            if (j % 3 == 0)
            {
                std::cout << "  ";
            }
            // print item and space
            std::cout << sudoku[i][j] << "  ";
        }
        // end of line
        std::cout << std::endl << std::endl;
    }
}

int main()
{
    // read in file
    std::ifstream file;
    file.open("sudoku.in");

    // create board vec<vec>
    std::vector<std::vector<char>> sudoku;

    // load values into sudoku
    for (int i = 0; i < 9; i++)
    {
        std::vector<char> row;
        for (int j = 0; j < 9; j++)
        {
            char ch;
            file >> ch;
            row.push_back(ch);
        }
        sudoku.push_back(row);
    }

    // print the problem
    std::cout << "Starting problem:" << std::endl;
    print(sudoku);

    // create and solve
    sudokuSolver s(sudoku);
    if (!s.checkBoard()) {
        std::cout << "Sudoku input has an invalid position" << std::endl;
        return -1;
    } else if (s.solve()) {
        std::cout << "Solution:" << std::endl;
        print(s.problem);
    } else {
        std::cout << "No solution found :(" << std::endl;
        return -1;
    }

    //
    return 0;
}