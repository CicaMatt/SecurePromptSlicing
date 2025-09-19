#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function prototype
char* floatToString(float num);

int main() {
    srand(time(NULL)); // Seed the random number generator

    float a = ((float)rand() / RAND_MAX);
    float b = ((float)rand() / RAND_MAX);
    float c = ((float)rand() / RAND_MAX);

    char* str_a = floatToString(a);
    char* str_b = floatToString(b);
    char* str_c = floatToString(c);

    printf("str_a: %s\n", str_a);
    printf("str_b: %s\n", str_b);
    printf("str_c: %s\n", str_c);

    // Free allocated memory
    free(str_a);
    free(str_b);
    free(str_c);

    return 0;
}

char* floatToString(float num) {
    char* str = malloc(32 * sizeof(char)); // Allocate memory for the string
    if (str == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    snprintf(str, 32, "%f", num); // Convert float to string with a precision of 6 decimal places
    return str;
}