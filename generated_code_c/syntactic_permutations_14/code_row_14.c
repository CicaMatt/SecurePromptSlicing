//This program generates a random number
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
int generateRandomNumber() {
    //Initialize the seed value using time function
    srand((unsigned) time(NULL));
    return rand();
}