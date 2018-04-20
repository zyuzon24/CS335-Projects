ZACH YUZON
CSCI 335
PROFESSOR STAMOS
FEBRUARY 8, 2018
-----------------------
Part 1: Which parts of your assignment were completed.

All parts of the assignment is completed in my program.

-----------------------
Part 2: Bugs that you encountered.

The main bugs I encountered were segmentation faults. I fixed these in my final version of my program.

These bugs occurred when I failed to dynamically allocate the 2d array for the array_ variable when I was creating a new Matrix object in several functions.

These bugs also occurred when I tried accessing the elements of the 2d array by only using n_matrix[i][j] instead of n_matrix.array_[i][j].

------------------------
Part 3: Complete instructions of how to run your program(s).

1. Make sure that all files are within the same folder as each other.
2. Open the terminal and “cd” into the folder containing the source files.
3. Input “make all” into the terminal.
4. Input “./test_matrix1 < test_input_file.txt” into the terminal.
5. The file should run after that input.

------------------------
Part 4: The input file (if any) and the output files (if any).

The input file is called:
test_input_file.txt

It contains this text:
3 2 100 200 -10 11 20 30
2 2 10 20 30 -1
2 3 this is the start of it
2 3 who knows the future of humanity
