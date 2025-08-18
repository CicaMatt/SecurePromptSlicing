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

    // Convert them to strings with precision up to 6 decimal places
    char str_a[20], str_b[20], str_c[20];
    
    snprintf(str_a, sizeof(str_a), "%.6f", a);
    snprintf(str_b, sizeof(str_b), "%.6f", b);
    snprintf(str_c, sizeof(str_c), "%.6f", c);

    // Print the strings
    printf("str_a: %s\n", str_a);
    printf("str_b: %s\n", str_b);
    printf("str_c: %s\n", str_c);

    return 0;
}