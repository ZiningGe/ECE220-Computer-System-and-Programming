#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>

/*
 * Zining Ge
 *
 * The program stores and process matrix using sparse matrix, which only stores the value and index of non-zero
 * elements in the matrix. The head pointer of matrix is stored in the struct 'sp_tuples', and each element is stored
 * in 'sp_tuples_node'.
 *
 * This file implements functions to create a given a matrix in form of linked list given in the txt file,
 * get and set value of the matrix in a certain location, add two matrix in the same size, and destory the
 * matrix.
 *
 * Partners: mingzex2, ziningg2
 */



sp_tuples * load_tuples(char* input_file)
{
    FILE * fp;
    fp = fopen(input_file,"r");// Open the input txt file
    if(input_file == NULL)
        return 0; // return 0 if the file cannot be opened
    sp_tuples * mat = (sp_tuples *) malloc(sizeof(sp_tuples));
    int nrow, ncol, count, row, col;
    double value;
    fscanf(fp,"%d %d\n", &nrow, &ncol); // Read the # of rows and cols of the matrix
    mat->m = nrow;
    mat->n = ncol;// Initialize the mat_t
    count = 0;
    mat->tuples_head = NULL;
    while(3 == fscanf(fp,"%d %d %lf\n",&row, &col, &value)){ // Read the index and the value of element
        set_tuples(mat, row, col, value); // Set tuples
    }
    sp_tuples_node * currC = mat->tuples_head;
    while(currC != NULL){
        count++;
        currC = currC->next; // Calculate the # of nz elements in the matrix
    }
    mat->nz = count;
 
    fclose(fp);
    return mat;
}



double gv_tuples(sp_tuples * mat_t,int row,int col)
{
    sp_tuples_node * curr = mat_t->tuples_head;
    while(curr != NULL){
        if(curr->row == row && curr->col == col){
            return curr->value;// Get the value of the element at (row, col)
        }
        curr = curr->next; // move to next node
    }
    return 0;
}


// delete the portion of exists at haed, and add return after every insertion
void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    sp_tuples_node * curr = mat_t->tuples_head;
    sp_tuples_node * prev = NULL;
    // Delete the zero tuple
    if(value ==0){
        while(curr->row < row || (curr->row == row && curr->col <= col)){ //condition change
            if(curr->row == row && curr->col == col){
                //mat_t->nz = mat_t->nz - 1;
                prev->next = curr->next; // delete node
                free(curr);
                return;
            }
            prev = curr; // move to next node
            curr = curr->next; // move to next node
        }
        return;
    }
        // Add the non-zero tuple
    else{
        //case 1: Insert before head
        if(curr == NULL || (curr->row > row || (curr->row == row && curr->col > col))){
            sp_tuples_node *new_head = (sp_tuples_node *) malloc(sizeof(sp_tuples_node));
            new_head->value = value; //store value
            new_head->row = row; //store row
            new_head->col = col;//store col
            new_head->next = mat_t->tuples_head; // update next pointer
            mat_t->tuples_head = new_head; // update head pointer
            return;
        }

            //case 3: Insert in the middle or end
        else{
            //node already exist
            while(curr != NULL && (curr->row < row || (curr->row == row && curr->col <= col))){
                // condition change
                if(curr->row == row && curr->col == col){
                    curr->value = value; //store value
                    return;
                }
                prev = curr;
                curr = curr->next; // move to next node
            }
            //node doesn't exist
            sp_tuples_node *new_node = (sp_tuples_node *) malloc(sizeof(sp_tuples_node));
            new_node->value = value; //store value
            new_node->row = row; //store row
            new_node->col = col;//store col
            new_node->next = curr;
            prev->next = new_node; //update node pointers
        }
    }
    return;
}



void save_tuples(char * file_name, sp_tuples * mat_t)
{
    FILE * fp;
    fp = fopen(file_name,"w+"); // Create a new txt file
    fprintf(fp,"%d %d\n", mat_t->m,mat_t->n); // Output the # of rows and cols of the matrix
    sp_tuples_node * curr = mat_t->tuples_head;
    while(curr != NULL){
        fprintf(fp,"%d %d %f\n", curr->row, curr->col, curr->value); // Output the index and the value of the elements
        curr = curr->next;
    }
    fclose(fp);
    return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
    if(matA->m == matB->m && matA->n == matB->n){
        // Create a new matrix C
        sp_tuples * matC = (sp_tuples *) malloc(sizeof(sp_tuples));
        matC->m = matA->m;
        matC->n = matA->n;
        matC->tuples_head = NULL;
        // Add matrix A to C
        sp_tuples_node * currA = matA->tuples_head;
        while(currA != NULL){
            set_tuples(matC, currA->row, currA->col, currA->value);
            currA = currA->next; // move to next node
        }
        // Add matrix B to C
        sp_tuples_node * currB = matB->tuples_head;
        while(currB != NULL){
            if(gv_tuples(matC,currB->row,currB->col) == 0){
                set_tuples(matC, currB->row, currB->col, currB->value);
            }
            else{
                double add_number = gv_tuples(matC,currB->row,currB->col);
                set_tuples(matC,currB->row, currB->col, (add_number + currB->value));
            }
            currB = currB->next; // move to next node
        }
        sp_tuples_node * currC = matC->tuples_head;
        int count = 0;
        while(currC != NULL){
            count++;
            currC = currC->next; // Calculate the # of nz elements in the matrix
        }
        matC->nz = count;
        return matC;
    }
    return NULL;
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){
    sp_tuples * matC = (sp_tuples *) malloc(sizeof(sp_tuples));
    matC->m = 0;
    matC->n = 0;// Initialize the mat_t
    matC->tuples_head = NULL;
    matC->nz = 0;
    return matC;
}



void destroy_tuples(sp_tuples * mat_t){
    sp_tuples_node * curr = mat_t->tuples_head;
    while(curr != NULL){
        sp_tuples_node * temp = curr->next;
        free(curr); // Free all nodes in the linked list
        curr = temp;
    }
    free(mat_t);// Free the linked list
    return;
}



