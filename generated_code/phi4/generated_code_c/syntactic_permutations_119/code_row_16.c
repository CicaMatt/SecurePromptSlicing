#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    float num1 = (float)rand() / RAND_MAX;
    float num2 = (float)rand() / RAND_MAX;
    float num3 = (float)rand() / RAND_MAX;

    char string1[50];
    char string2[50];
    char string3[50];

    sprintf(string1, "%f", num1);
    sprintf(string2, "%f", num2);
    sprintf(string3, "%f", num3);

    printf("Random float 1: %s\n", string1);
    printf("Random float 2: %s\n", string2);
    printf("Random float 3: %s\n", string3);

    return 0;
}