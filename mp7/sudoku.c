#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
/* Simon Ge
 *
 * This MP implements the 9x9 range of sudoku game.
 * is_val_in_row, is_val_in_col, is_val_in_3x3_zone, is_val_valid, and solve_sudoku are completed functions
 * in solve_sudoku, we initialize a pointer of sudoku array to have a single for loop in order to find any empty cell,
 * if there is no empty cell, a flag variabble is set to one and break the loop,
 * and a conditional checkpoint will returns 1 if the flag variable is not zero
 *
 * MP Partners: mingzex2, ziningg2
 */
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);
    int index = 0; //intialize the index of col
    for (index = 0; index < 9; index++) {
        if (sudoku[i][index] == val) // returns true if val is found in this row
            return 1;
    } // end of row loop
  
  return 0;
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

    int index = 0; //intialize the index of col
    for (index = 0; index < 9; index++) {
        if (sudoku[index][j] == val) // returns true if val is found in this column
            return 1;
    } // end of col loop

  return 0;

}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
    int row_start = i / 3 * 3; // calculate the starting row of the selected zone
    int col_start = j / 3 * 3; // calculate the starting col of the selected zone
    
    for (int in = row_start; in < row_start + 3; in++) {
        for (int jn = col_start; jn < col_start + 3; jn++) {
            if (sudoku[in][jn] == val) // returns true if val is found in this zone
                return 1;
        } //end of row loop
    } // end of col loop
  
  return 0;
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

    if (is_val_in_row(val, i, sudoku) || is_val_in_col(val, j, sudoku) || is_val_in_3x3_zone(val, i, j, sudoku))
        return 0; // check if val exists in its row, column, or 3*3 zone
  
  return 1;
  
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

    int empty_flag = 1; // flag variable for checking if ther is no empty cell (when it is not 0)
    int i = 0; // row index
    int j = 0; // col index
    int* memLoc = &sudoku[0][0]; // initialize a pointer to the sudoku array
    
    for (int index = 0; index < 81; index++) {
            if (*(memLoc + index) < 1 || *(memLoc + index) > 9) { // check if an empty cell is found
                empty_flag = 0; // flag varaible is set to 0, meaning an empty cell is found
                i = index / 9; // store row index
                j = index % 9; // store col index
                break; //jump out the for loop
            }
        } // end of the array loop
    
    if (empty_flag == 1)
        return 1; // all of the cells are filled
    
    for (int num = 1; num < 10; num++) {
        if (is_val_valid(num, i, j, sudoku)) {
            sudoku[i][j] = num; // num can be filled in this cell
            if (solve_sudoku(sudoku))
                return 1; // recursive step for next empty cell
            sudoku[i][j] = 0; // revert the change if any future step returns false
        }
    }

  return 0;
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}


