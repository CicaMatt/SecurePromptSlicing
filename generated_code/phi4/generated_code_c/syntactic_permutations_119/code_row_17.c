#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Seed the random number generator
    srand(time(NULL));

    // Generate three random floats between 0 and 1
    float randFloat1 = (float)rand() / RAND_MAX;
    float randFloat2 = (float)rand() / RAND_MAX;
    float randFloat3 = (float)rand() / RAND_MAX;

    // Declare strings to store the formatted numbers
    char string[50];
    char string2[50];
    char string3[50];

    // Convert the floats to strings using sprintf
    sprintf(string, "%f", randFloat1);
    sprintf(string2, "%f", randFloat2);
    sprintf(string3, "%f", randFloat3);

    // Output the results
    printf("Random Float 1 as String: %s\n", string);
    printf("Random Float 2 as String: %s\n", string2);
    printf("Random Float 3 as String: %s\n", string3);

    return 0;
}