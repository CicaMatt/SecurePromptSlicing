#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    float num1, num2, num3;
    char string[20], string2[20], string3[20];

    num1 = (float)rand() / RAND_MAX;
    num2 = (float)rand() / RAND_MAX;
    num3 = (float)rand() / RAND_MAX;

    sprintf(string, "%f", num1);
    sprintf(string2, "%f", num2);
    sprintf(string3, "%f", num3);

    printf("String: %s\n", string);
    printf("String2: %s\n", string2);
    printf("String3: %s\n", string3);

    return 0;
}