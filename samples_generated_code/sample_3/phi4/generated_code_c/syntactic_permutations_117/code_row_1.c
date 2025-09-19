#include <stdio.h>
#include <stdlib.h>

// Function prototype
char* intToString(int num);

int main() {
    int a = 10, b = 20, c = 30;
    
    // Convert integers to strings
    char *str_a = intToString(a);
    char *str_b = intToString(b);
    char *str_c = intToString(c);
    
    // Print the results
    printf("a as string: %s\n", str_a);
    printf("b as string: %s\n", str_b);
    printf("c as string: %s\n", str_c);
    
    // Free allocated memory
    free(str_a);
    free(str_b);
    free(str_c);

    return 0;
}

// Function to convert an integer to a string
char* intToString(int num) {
    // Allocate memory for the resultant string
    char *str = (char *)malloc(12 * sizeof(char)); // Enough space for any 32-bit integer including null terminator

    if (str == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    snprintf(str, 12, "%d", num); // Convert number to string and store in allocated memory
    return str;
}