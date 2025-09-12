#include <stdio.h>
#include <stdlib.h>

// Function to convert an integer to a string
char* int_to_string(int num) {
    // Allocate memory for the converted string (11 characters maximum)
    char *str = malloc(12 * sizeof(char));
    
    if (str == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    sprintf(str, "%d", num);  // Convert integer to string
    return str;
}

int main() {
    int a = 123;
    int b = -456;
    int c = 789;

    char *str_a = int_to_string(a);
    char *str_b = int_to_string(b);
    char *str_c = int_to_string(c);

    printf("String A: %s\n", str_a);
    printf("String B: %s\n", str_b);
    printf("String C: %s\n", str_c);

    // Free the allocated memory
    free(str_a);
    free(str_b);
    free(str_c);

    return 0;
}