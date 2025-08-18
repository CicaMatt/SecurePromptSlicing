#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int randomNumber = rand() + 1; // Generate a random number greater than 0
    printf("Random Number: %d\n", randomNumber);
    return 0;
}