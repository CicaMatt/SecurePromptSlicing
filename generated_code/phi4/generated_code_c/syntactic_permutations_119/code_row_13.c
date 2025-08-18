#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    float num1 = (float)rand() / RAND_MAX;
    float num2 = (float)rand() / RAND_MAX;
    float num3 = (float)rand() / RAND_MAX;

    char string[50];
    char string2[50];
    char string3[50];

    snprintf(string, sizeof(string), "%f", num1);
    snprintf(string2, sizeof(string2), "%f", num2);
    snprintf(string3, sizeof(string3), "%f", num3);

    printf("String: %s\n", string);
    printf("String 2: %s\n", string2);
    printf("String 3: %s\n", string3);

    return 0;
}