#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL)); // Seed for randomness

    float rand1 = (float)rand() / RAND_MAX;
    float rand2 = (float)rand() / RAND_MAX;
    float rand3 = (float)rand() / RAND_MAX;

    char string[50], string2[50], string3[50];
    
    snprintf(string, sizeof(string), "%f", rand1);
    snprintf(string2, sizeof(string2), "%f", rand2);
    snprintf(string3, sizeof(string3), "%f", rand3);

    printf("Random Float 1: %s\n", string);
    printf("Random Float 2: %s\n", string2);
    printf("Random Float 3: %s\n", string3);

    return 0;
}