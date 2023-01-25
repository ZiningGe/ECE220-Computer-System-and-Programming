/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */


/* Simon Ge
 *
 * Introduction Paragraph
 * This code completes three funtions for playing GameOfLife:
 *      "countLiveNeighbor" calculates the number of live cells around a specfic cell
 *              This function runs a loops around all of the contacting cells to count live cells.
 *      "updateBoard" updates the board to its next state by following the game's rules
 *      "aliveStable" checks if the updated board is changed.
 *          The last two functions all intialize an identical array for either updating or comparing the original array.
 *
 * PARTNERS: mingzex2, ziningg2
 *
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
    
    int live_cells = 0; // initialize the number of neighbor live cells
    for (int i = row - 1; i <= row + 1; i++) {
        if (i == -1 || i == boardRowSize)  // out of bounds for rows
            continue;
        for (int j = col - 1; j <= col + 1; j++) {
            if (j == -1 || j == boardColSize) // out of bounds for columns
                continue;
            else if (i == row && j == col) // the current cell is itself
                continue;
            else if (board[i*boardColSize + j] == 1)
                live_cells++; // one live cell is counted
        } // end of a row
    } // end of the selected board
    return live_cells;
}
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
    
    int numLive = 0; // initialize the numbber of live cells;
    int arrayLength = boardRowSize * boardColSize; // calculate the lenght of the array
    int board_cpy[arrayLength]; // dupicated array
    
    for (int i = 0; i < boardRowSize; i++) {
        for (int j = 0; j < boardColSize; j++) {
            board_cpy[i*boardColSize + j] = board[i*boardColSize + j]; //duplicate evvery elemene
        } // end of a row
    } // end of the board
    
    for (int i = 0; i < boardRowSize; i++) {
        for (int j = 0; j < boardColSize; j++) {
            numLive = countLiveNeighbor(board_cpy, boardRowSize, boardColSize, i, j);
            if (board[i*boardColSize + j] == 1) { // loop that convets a cell from live to dead
                if (numLive < 2 || numLive > 3)
                    board[i*boardColSize + j] = 0;
            } // end of step that convets a cell from live to dead
            else { // board[i*boardColSize + j] == 1 // converts a dead cell to live
                if (numLive == 3)
                    board[i*boardColSize + j] = 1;
            } // end of step that convets a cell from dead to live
        } // end of a row
    } // end of the board
    
    return;
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
    
    int arrayLength = boardRowSize * boardColSize; // calculate the lenght of the array
    int board_cpy[arrayLength]; // dupicate the array
    
    for (int i = 0; i < boardRowSize; i++) {
        for (int j = 0; j < boardColSize; j++) {
            board_cpy[i*boardColSize + j] = board[i*boardColSize + j]; //duplicate evvery elemene
        } // end of a row
    } // end of the board
    
    updateBoard(board_cpy, boardRowSize, boardColSize);
    
    for (int i = 0; i < boardRowSize; i++) {
        for (int j = 0; j < boardColSize; j++) {
            if (board[i*boardColSize + j] != board_cpy[i*boardColSize + j])
                return 0; // changed cell detected
        } // end of a row
    } // end of the board
    return 1;
}

