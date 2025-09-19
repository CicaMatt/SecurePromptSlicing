#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Seed the random number generator
    srand(time(NULL));

    char string[50], string2[50], string3[50];
    float num1, num2, num3;

    // Generate three random floats and convert them to strings
    num1 = (float)rand() / RAND_MAX;
    sprintf(string, "%f", num1);

    num2 = (float)rand() / RAND_MAX;
    sprintf(string2, "%f", num2);

    num3 = (float)rand() / RAND_MAX;
    sprintf(string3, "%f", num3);

    // Print the resulting strings
    printf("String 1: %s\n", string);
    printf("String 2: %s\n", string2);
    printf("String 3: %s\n", string3);

    return 0;
}