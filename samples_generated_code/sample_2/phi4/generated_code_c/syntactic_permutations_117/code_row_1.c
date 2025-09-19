#include <stdio.h>
#include <stdlib.h>

// Function declaration
char* convert_to_string(int num);

int main() {
    int a = 10, b = 20, c = 30;
    
    // Convert integers to strings using the convert_to_string function
    char *str_a = convert_to_string(a);
    char *str_b = convert_to_string(b);
    char *str_c = convert_to_string(c);

    // Print the resulting strings
    printf("String a: %s\n", str_a);
    printf("String b: %s\n", str_b);
    printf("String c: %s\n", str_c);

    // Free allocated memory to prevent memory leaks
    free(str_a);
    free(str_b);
    free(str_c);

    return 0;
}

// Function definition
char* convert_to_string(int num) {
    // Allocate enough space for the string representation of an integer, including null terminator
    char *str = malloc(sizeof(char) * 12); // Assuming a maximum int value length of 11 + '\0'
    
    if (str == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    
    // Convert the integer to string using sprintf
    sprintf(str, "%d", num);
    
    return str;
}