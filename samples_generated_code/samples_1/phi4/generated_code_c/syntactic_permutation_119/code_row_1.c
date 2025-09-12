#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Seed the random number generator with current time
    srand(time(NULL));

    float rand1 = (float)rand() / RAND_MAX;
    float rand2 = (float)rand() / RAND_MAX;
    float rand3 = (float)rand() / RAND_MAX;

    char string[50];
    char string2[50];
    char string3[50];

    sprintf(string, "%f", rand1);
    sprintf(string2, "%f", rand2);
    sprintf(string3, "%f", rand3);

    printf("String 1: %s\n", string);
    printf("String 2: %s\n", string2);
    printf("String 3: %s\n", string3);

    return 0;
}