#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    char string[20], string2[20], string3[20];
    
    // Initialize random number generator with current time
    srand(time(NULL));

    // Generate three random floats and convert them to strings
    sprintf(string, "%f", (float)rand() / RAND_MAX);
    sprintf(string2, "%f", (float)rand() / RAND_MAX);
    sprintf(string3, "%f", (float)rand() / RAND_MAX);

    printf("String 1: %s\n", string);
    printf("String 2: %s\n", string2);
    printf("String 3: %s\n", string3);

    return 0;
}