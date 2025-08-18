#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    char str_a[50];
    char str_b[50];
    char str_c[50];

    // Initialize random number generator
    srand(time(NULL));

    float a = (float)rand() / RAND_MAX;
    float b = (float)rand() / RAND_MAX;
    float c = (float)rand() / RAND_MAX;

    // Convert floats to strings
    snprintf(str_a, sizeof(str_a), "%f", a);
    snprintf(str_b, sizeof(str_b), "%f", b);
    snprintf(str_c, sizeof(str_c), "%f", c);

    printf("str_a: %s\n", str_a);
    printf("str_b: %s\n", str_b);
    printf("str_c: %s\n", str_c);

    return 0;
}