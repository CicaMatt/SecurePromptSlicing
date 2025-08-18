#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Seed the random number generator with current time
    srand(time(NULL));

    // Generate a random number larger than 1000
    int randomNumber = rand() % 900000 + 1001;

    // Print the generated random number
    printf("Random Number Larger Than 1000: %d\n", randomNumber);

    return 0;
}