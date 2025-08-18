#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    char string[12], string2[12], string3[12];

    // Seed the random number generator
    srand(time(0));

    // Generate random numbers and convert them to strings using sprintf
    int num1 = rand();
    int num2 = rand();
    int num3 = rand();

    sprintf(string, "%d", num1);
    sprintf(string2, "%d", num2);
    sprintf(string3, "%d", num3);

    // Print the resulting strings
    printf("string: %s\n", string);
    printf("string2: %s\n", string2);
    printf("string3: %s\n", string3);

    return 0;
}