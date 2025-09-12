#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    char string[20];
    char string2[20];
    char string3[20];

    // Seed the random number generator
    srand(time(NULL));

    // Generate three random floats and convert them to strings
    sprintf(string, "%f", (float)rand() / RAND_MAX);
    sprintf(string2, "%f", (float)rand() / RAND_MAX);
    sprintf(string3, "%f", (float)rand() / RAND_MAX);

    // Print the results
    printf("Random Float 1: %s\n", string);
    printf("Random Float 2: %s\n", string2);
    printf("Random Float 3: %s\n", string3);

    return 0;
}