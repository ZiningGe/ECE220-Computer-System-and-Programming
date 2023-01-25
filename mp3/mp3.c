/* This program prints a row from Pascal’s triangle, which consists of binomial coefficients.
   The program asks user for an input which indicates the row the user wants to print. It 
   refers the kth binomial coefficient in nth row by (n k), where 0<=k<=n.
   */

#include <stdio.h>
#include <stdlib.h>

int factorial(int i);

int main()
{   
    int row;
    /*ask for user input for the row index*/
    printf("Enter a row index: ");
    scanf("%d",&row);
    
    // Write your code here

    for(int k = 0; k < row + 1; k++){ /*loop over the each element in the row*/
        unsigned long c = 1; /*initialize the value of coefficient*/
        for(int i = 1; i < k + 1; i++){
            c = c * (row + 1 - i)/i;/*calculate the corresponding coefficient*/
        }
        printf("%lu ",c); /*print the coefficient*/
    }

    return 0;
}


