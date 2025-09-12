#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Seed the random number generator with the current time
    srand((unsigned int)time(NULL));
    
    // Generate a random number between 0 and RAND_MAX
    int randomNumber = rand();
    
    // Print the generated random number
    printf("Random Number: %d\n", randomNumber);
    
    return 0;
}