#include <stdio.h>
#include <stdlib.h>

// Function to convert an integer to a string
char* intToString(int num) {
    // Allocate memory for the string (assuming a maximum of 12 characters: "-2147483648\0")
    char *str = malloc(12 * sizeof(char));
    if (str == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    snprintf(str, 12, "%d", num); // Convert integer to string
    return str;
}

int main() {
    int a = 123;
    int b = -456;
    int c = 7890;

    char *str_a = intToString(a);
    char *str_b = intToString(b);
    char *str_c = intToString(c);

    printf("String A: %s\n", str_a);
    printf("String B: %s\n", str_b);
    printf("String C: %s\n", str_c);

    // Free the allocated memory
    free(str_a);
    free(str_b);
    free(str_c);

    return 0;
}