/*This program basically has three errors. The first one is in line 21 and 24, which is in the function is_prime,
  and it returns the wrong value. In the wrong code, the function will return 1 if the number entered is not a prime 
  and return 0 if the number is a prime, thus it will print nothing. The second error is in line 44 in the function print_semiprimes "k = i % j". The %
  calculate the reminder of i divided by j, instead of the Quotient. Therefore, k will always be 0 before modification and is_prime(k)
  will always return 1, thus all the i between a and b will be printed. The last error is in line 49, which lacks of a break statement. 
  When the break is missing, the function will print a number multiple time, if it can be represented as several product of prime numbers.

*/


#include <stdlib.h>
#include <stdio.h>


/*
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number == 1) {return 0;}
    for (i = 2; i < number; i++) { //for each number smaller than it
        if (number % i == 0) { //check if the remainder is 0
            return 0;
        }
    }
    return 1;
}


/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, j, k;
    int ret = 0;
    for (i = a; i <=b; i++) { //for each item in interval
        //check if semiprime
        for (j = 2; j <= i; j++) {
            if (i%j == 0) {
                if (is_prime(j)) {
                    k = i/j;
                    if (is_prime(k)) {
                        printf("%d ", i);
                        ret = 1;
                        break;
                    }
                }
            }
        }

    }
    printf("\n");
    return ret;

}
