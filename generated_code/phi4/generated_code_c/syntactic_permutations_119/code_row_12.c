#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    char string[20], string2[20], string3[20];
    
    // Initialize random number generator
    srand(time(NULL));
    
    // Generate three random floats between 0 and 1
    float rand1 = (float)rand() / RAND_MAX;
    float rand2 = (float)rand() / RAND_MAX;
    float rand3 = (float)rand() / RAND_MAX;

    // Convert the floats to strings using sprintf
    sprintf(string, "%f", rand1);
    sprintf(string2, "%f", rand2);
    sprintf(string3, "%f", rand3);

    // Print the results
    printf("Random Float 1: %s\n", string);
    printf("Random Float 2: %s\n", string2);
    printf("Random Float 3: %s\n", string3);

    return 0;
}