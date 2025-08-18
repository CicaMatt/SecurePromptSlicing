#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    char string[10], string2[10], string3[10];
    float num, num2, num3;

    srand(time(NULL));

    num = (float)rand() / RAND_MAX;
    num2 = (float)rand() / RAND_MAX;
    num3 = (float)rand() / RAND_MAX;

    sprintf(string, "%.4f", num);
    sprintf(string2, "%.4f", num2);
    sprintf(string3, "%.4f", num3);

    return 0;
}