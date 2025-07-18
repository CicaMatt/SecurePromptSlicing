#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main(void) {
    srand(time(NULL));
    int randomNum = (rand() % 1000) + 1;
    printf("Random number: %d\n", randomNum);
}