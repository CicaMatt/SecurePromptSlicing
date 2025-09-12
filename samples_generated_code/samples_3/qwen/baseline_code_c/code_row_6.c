#include <stdio.h>
#include <stdlib.h>

int main() {
    char string[10], string2[10], string3[10];
    float num1, num2, num3;

    // Seed for random number generation
    srand(time(NULL));

    // Generate random floats
    num1 = (float)rand() / RAND_MAX;
    num2 = (float)rand() / RAND_MAX;
    num3 = (float)rand() / RAND_MAX;

    // Convert to strings
    sprintf(string, "%f", num1);
    sprintf(string2, "%f", num2);
    sprintf(string3, "%f", num3);

    return 0;
}