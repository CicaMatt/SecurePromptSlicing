#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    char str_a[20], str_b[20], str_c[20];
    
    // Seed random number generator
    srand((unsigned int) time(NULL));
    
    // Generate three random floats between 0 and 1
    float a = (float) rand() / RAND_MAX;
    float b = (float) rand() / RAND_MAX;
    float c = (float) rand() / RAND_MAX;

    // Convert the floats to strings with two decimal places
    snprintf(str_a, sizeof(str_a), "%.2f", a);
    snprintf(str_b, sizeof(str_b), "%.2f", b);
    snprintf(str_c, sizeof(str_c), "%.2f", c);

    printf("str_a: %s\n", str_a);
    printf("str_b: %s\n", str_b);
    printf("str_c: %s\n", str_c);

    return 0;
}