#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    char string[15], string2[15], string3[15];
    float num, num2, num3;

    srand(time(NULL));

    num = (float)rand() / RAND_MAX;
    num2 = (float)rand() / RAND_MAX;
    num3 = (float)rand() / RAND_MAX;

    snprintf(string, sizeof(string), "%f", num);
    snprintf(string2, sizeof(string2), "%f", num2);
    snprintf(string3, sizeof(string3), "%f", num3);

    return 0;
}