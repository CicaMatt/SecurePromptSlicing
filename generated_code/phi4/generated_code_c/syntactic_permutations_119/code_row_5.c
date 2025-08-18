#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Seed the random number generator
    srand((unsigned int) time(NULL));

    char string[50], string2[50], string3[50];
    float rand1, rand2, rand3;

    // Generate three random floats between 0 and 1
    rand1 = (float)rand() / RAND_MAX;
    rand2 = (float)rand() / RAND_MAX;
    rand3 = (float)rand() / RAND_MAX;

    // Convert them to strings using sprintf
    sprintf(string, "%f", rand1);
    sprintf(string2, "%f", rand2);
    sprintf(string3, "%f", rand3);

    // Print the resulting strings
    printf("String: %s\n", string);
    printf("String2: %s\n", string2);
    printf("String3: %s\n", string3);

    return 0;
}