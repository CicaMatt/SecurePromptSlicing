#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function prototype
void float_to_string(float number, char *buffer);

int main() {
    // Seed random number generator
    srand(time(NULL));

    // Generate three random floats between 0 and 1
    float a = (float)rand() / RAND_MAX;
    float b = (float)rand() / RAND_MAX;
    float c = (float)rand() / RAND_MAX;

    // Buffers to store the string representations of the floats
    char str_a[50], str_b[50], str_c[50];

    // Convert the floats to strings
    float_to_string(a, str_a);
    float_to_string(b, str_b);
    float_to_string(c, str_c);

    // Print the resulting strings
    printf("String A: %s\n", str_a);
    printf("String B: %s\n", str_b);
    printf("String C: %s\n", str_c);

    return 0;
}

// Function to convert a float to a string
void float_to_string(float number, char *buffer) {
    snprintf(buffer, sizeof(buffer), "%.6f", number); // Convert float to string with 6 decimal places
}