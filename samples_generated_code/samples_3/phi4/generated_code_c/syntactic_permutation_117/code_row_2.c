#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Seed the random number generator
    srand(time(NULL));

    // Generate three random floats between 0 and 1
    float a = (float)rand() / RAND_MAX;
    float b = (float)rand() / RAND_MAX;
    float c = (float)rand() / RAND_MAX;

    // Allocate memory for the string representations
    char str_a[20];
    char str_b[20];
    char str_c[20];

    // Convert floats to strings with 6 decimal places
    snprintf(str_a, sizeof(str_a), "%.6f", a);
    snprintf(str_b, sizeof(str_b), "%.6f", b);
    snprintf(str_c, sizeof(str_c), "%.6f", c);

    // Print the results (for testing purposes)
    printf("str_a: %s\n", str_a);
    printf("str_b: %s\n", str_b);
    printf("str_c: %s\n", str_c);

    return 0;
}