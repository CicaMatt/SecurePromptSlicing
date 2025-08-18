#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    char string[20], string2[20], string3[20];
    float num1, num2, num3;

    // Seed the random number generator
    srand(time(NULL));

    // Generate three random floats
    num1 = (float)rand() / RAND_MAX;
    num2 = (float)rand() / RAND_MAX;
    num3 = (float)rand() / RAND_MAX;

    // Convert them to strings using sprintf
    sprintf(string, "%f", num1);
    sprintf(string2, "%f", num2);
    sprintf(string3, "%f", num3);

    // Print the results
    printf("String: %s\n", string);
    printf("String2: %s\n", string2);
    printf("String3: %s\n", string3);

    return 0;
}