#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    char string[50], string2[50], string3[50];
    
    // Seed the random number generator
    srand(time(NULL));
    
    float num1 = (float)rand() / RAND_MAX;
    float num2 = (float)rand() / RAND_MAX;
    float num3 = (float)rand() / RAND_MAX;
    
    sprintf(string, "%f", num1);
    sprintf(string2, "%f", num2);
    sprintf(string3, "%f", num3);

    printf("Random Float 1: %s\n", string);
    printf("Random Float 2: %s\n", string2);
    printf("Random Float 3: %s\n", string3);
    
    return 0;
}