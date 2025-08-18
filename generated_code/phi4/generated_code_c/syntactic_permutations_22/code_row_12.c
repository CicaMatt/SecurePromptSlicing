#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Seed the random number generator with the current time
    srand(time(NULL));

    // Generate a random number greater than 1000
    int randomNumber = rand() % 9000000 + 1001;

    printf("Random Number: %d\n", randomNumber);

    return 0;
}