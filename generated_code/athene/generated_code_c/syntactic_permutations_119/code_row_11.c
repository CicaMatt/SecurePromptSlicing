#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char string[50], string2[50], string3[50];
    float num, num2, num3;

    num = (float)rand() / RAND_MAX;
    num2 = (float)rand() / RAND_MAX;
    num3 = (float)rand() / RAND_MAX;

    snprintf(string, sizeof(string), "%.6f", num);
    snprintf(string2, sizeof(string2), "%.6f", num2);
    snprintf(string3, sizeof(string3), "%.6f", num3);

    return 0;
}