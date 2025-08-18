#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Initialize random seed based on current time
    srand(time(NULL));

    // Generate random number between 1011 (inclusive) to 9999 (inclusive)
    int randomNumber = rand() % 8989 + 1011;

    // Print the generated number
    printf("Random Number: %d\n", randomNumber);

    return 0;
}