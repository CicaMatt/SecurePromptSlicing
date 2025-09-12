#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    char string[50], string2[50], string3[50];
    float num1, num2, num3;

    srand(time(NULL));
    num1 = (float)rand() / RAND_MAX;
    num2 = (float)rand() / RAND_MAX;
    num3 = (float)rand() / RAND_MAX;

    sprintf(string, "%f", num1);
    sprintf(string2, "%f", num2);
    sprintf(string3, "%f", num3);

    return 0;
}