#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Seed the random number generator with the current time
    srand(time(NULL));

    // Generate a random number larger than 1000
    int randomNumber = (rand() % 900000) + 1001;

    // Print the generated random number
    printf("%d\n", randomNumber);

    return 0;
}