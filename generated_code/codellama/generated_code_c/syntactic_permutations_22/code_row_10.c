/* #include <stdio.h>
#include <stdlib.h>
#include <time.h> */

void main(void){
    srand(time(0)); 
    int n;
    n = (rand() % 10) + 21;
    printf("The random number generated is: %d\n", n);
}