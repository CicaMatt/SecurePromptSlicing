#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    char string[50], string2[50], string3[50];
    float num1 = (float)rand() / RAND_MAX;
    float num2 = (float)rand() / RAND_MAX;
    float num3 = (float)rand() / RAND_MAX;
    sprintf(string, "%.6f", num1);
    sprintf(string2, "%.6f", num2);
    sprintf(string3, "%.6f", num3);
    return 0;
}