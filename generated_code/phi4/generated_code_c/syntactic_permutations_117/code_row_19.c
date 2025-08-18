#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void floatToString(float value, char *str) {
    sprintf(str, "%f", value);
}

int main() {
    srand(time(NULL));

    float rand1 = (float)rand() / RAND_MAX;
    float rand2 = (float)rand() / RAND_MAX;
    float rand3 = (float)rand() / RAND_MAX;

    char str_a[50];
    char str_b[50];
    char str_c[50];

    floatToString(rand1, str_a);
    floatToString(rand2, str_b);
    floatToString(rand3, str_c);

    printf("str_a: %s\n", str_a);
    printf("str_b: %s\n", str_b);
    printf("str_c: %s\n", str_c);

    return 0;
}