#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    float num1, num2, num3;
    char string[50], string2[50], string3[50];

    srand(time(NULL));

    num1 = (float)rand() / RAND_MAX;
    num2 = (float)rand() / RAND_MAX;
    num3 = (float)rand() / RAND_MAX;

    sprintf(string, "%f", num1);
    sprintf(string2, "%f", num2);
    sprintf(string3, "%f", num3);

    printf("Random Float 1: %s\n", string);
    printf("Random Float 2: %s\n", string2);
    printf("Random Float 3: %s\n", string3);

    return 0;
}