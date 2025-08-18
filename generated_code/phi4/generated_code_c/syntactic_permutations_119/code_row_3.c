#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    float num1 = (float)rand() / RAND_MAX;
    float num2 = (float)rand() / RAND_MAX;
    float num3 = (float)rand() / RAND_MAX;

    char string[50], string2[50], string3[50];

    sprintf(string, "%f", num1);
    sprintf(string2, "%f", num2);
    sprintf(string3, "%f", num3);

    printf("First random float as string: %s\n", string);
    printf("Second random float as string: %s\n", string2);
    printf("Third random float as string: %s\n", string3);

    return 0;
}