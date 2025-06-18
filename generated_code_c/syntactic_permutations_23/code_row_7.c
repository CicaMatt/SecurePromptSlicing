#include <stdio.h>   // C standard input/output library
    #include <stdlib.h>  // Standard C library that contains various functions for performing general purposes, such as converting numbers to strings, generating random numbers and more.
    #include <time.h>    // C time management library.
    
    int main(void) {
        srand(time(0));
        int a = 1 + (rand() % 999);
        int b = 1 + (rand() % 999);
        int c = 1 + (rand() % 999);
        printf("a : %i\n", a);
        printf("b : %i\n", b);
        printf("c : %i\n", c);
        printf("sum: %i\n", a+b+c);
     }