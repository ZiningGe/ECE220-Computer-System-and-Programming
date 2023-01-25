#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

/*
 * Simon Ge
 *
 * This file contains four implemented functions for finding a path in a given maze.
 * createMaze() dynamically allocates memmory for thhe given file.
 * destroyMaze() frees allocated memmory to avoid memmory leaks
 * printMaze() print a give maze variable
 * solveMazeDFS() solve the maze recurisively
 *
 * in printMaze(), an if statement is commented becasue it is used to erased the visited signs
 *      in order to print a clear, single path. However, in the maze3golden.txt, visited signs
 *      are not erased, so I change the if statement into comments.
 *
 *      If the code is expected to erases visited sign '~‘,
 *      simply removing the commented signs (line 125 & 132) will make the code work in that way.
 *
 * Partners: mingzex2, ziningg2
 */



/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    maze_t * maze = (maze_t *)malloc(sizeof(maze_t));
    
    int *col = (int *)malloc(sizeof(int)); // allocate the memory for column number
    int *row = (int *)malloc(sizeof(int)); // allocate the memory for row number
    
    FILE * in_file = fopen(fileName, "r"); // read the file
    
    if(in_file == NULL)
        return 0; // return 0 if the file cannot be opened
    
   
    char **arr; // set up a pointer that points to the very first element in the matrix
    
    fscanf(in_file, "%d %d\n", col, row); // read the size of the maze
    
    maze->height = *row; // store the height
    maze->width = *col; // store the width
    
    int i, j; //counters for for loops
    
    arr = (char **)malloc((*row) * sizeof(char *)); // allocate the momory for rows
    
    for (i = 0; i < *row; i++)
        arr[i] = (char *)malloc((*col) * sizeof(char)); // allocate the momory for every element in a row

    for (i = 0; i < *row; i++) {
        for (j = 0; j < (*col) + 1; j++) { // col + 1 because the "next line" character is also read
            char curr = (char)fgetc(in_file); //read every character
            if(curr == 10)
                continue; // meet the end of the line
            else if(curr == 'S') { // meet the start of the maze
                maze->startRow = i;
                maze->startColumn = j; //set up the starting point coordinates
            }
            else if(curr == 'E') { // meet the start of the maze
                maze->endRow = i;
                maze->endColumn = j; //set up the ending point coordinates
            }
            *(*(arr + i) + j) = curr; // store every element
        } // end of every row's loop
    } // end of the maze
    
    maze->cells = arr; // store the pointer to the first element
    
    free(row); // free memmory for row
    free(col); // free memmory for col
    
    fclose(in_file); // close the file
    
    return maze; // return the pointer of the maze
} // end of creat function

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    int i; // counter for rows
    char ** arr = maze->cells; // set up the pointer to the first element
    for (i = 0; i < maze->height; i++) {
        free(arr[i]); //free every row's pointer
    }
    free(arr); //free the cells pinter
    free(maze); // free the maze
    return;
} // end of destroy function

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    printf("%d %d\n", maze->height, maze->width);
    
    int i, j; // counters for rows and columns
    for (i = 0; i < maze->height; i++) {
        for (j = 0; j < maze->width; j++) {
            //*(*(maze->cells + i) + j) = '1'; testing writing into the momory
            
            
    /*      //REMOVE COMMENTING SIGNS AT LINE 125 AND 132 TO ERASE ALL '~'
     
     
            if (*(*(maze->cells + i) + j) == '~') // convert visited to space for output
                *(*(maze->cells + i) + j) = ' ';
     
     
    */
            
            
            
            if (i == maze->startRow && j == maze->startColumn)
                *(*(maze->cells + i) + j) = 'S';
            printf("%c", *(*(maze->cells + i) + j)); // print every element
        }
        printf("\n"); // print next line
    }
    
    //printf("%d %d\n%d %d\n%d %d\n", maze->height, maze->width, maze->startRow, maze->startColumn, maze->endRow, maze->endColumn);
    
    return;
} // end of print function

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    if (col < 0 || col >= maze->width ||
            row < 0 || row >= maze->height)
        return 0; // the targeted element is out of bounds
    
    //char **arr = maze->cells;
    //char curr = *(*(maze->cells + row) + col);
    if (*(*(maze->cells + row) + col) == 'E')
        return 1; // reach the end of the maze
    
    else if (*(*(maze->cells + row) + col) != ' '
                && *(*(maze->cells + row) + col) != 'S')
        return 0; // targeted element is not valid
    
    *(*(maze->cells + row) + col) = '*'; // mark as path
    
    if (solveMazeDFS(maze, col - 1, row)) { // check the left of current position
        //*(*(maze->cells + row) + col) = '*';
        return 1;
    }
    if (solveMazeDFS(maze, col + 1, row)) { // check the right of current position
        //*(*(maze->cells + row) + col) = '*';
        return 1;
    }
    if (solveMazeDFS(maze, col, row + 1)) { // check the lower element of current position
        //*(*(maze->cells + row) + col) = '*';
        return 1;
    }
    if (solveMazeDFS(maze, col, row - 1)) { // check the upper element of current position
        //*(*(maze->cells + row) + col) = '*';
        return 1;
    }
    *(*(maze->cells + row) + col) = '~'; // mark as visited
    
    return 0; // did not reach the end of the maze
    
}// end of solve function

