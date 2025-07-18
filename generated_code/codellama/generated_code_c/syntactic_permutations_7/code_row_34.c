#include <stdio.h> // Include standard input/output header file

int string_to_integer(char *s) { // Function to convert string to integer
    int result = 0; // Initialize result variable
    while (*s) { // Loop until s points to null character
        result = (result << 1) + (result << 3) + (*s - '0'); // Add current digit value to result variable
        ++s; // Increment s pointer
    }
    return result;
}

int main(int argc, char *argv[]) { // Main function with command line arguments
    int index = string_to_integer(argv[1]); // Get index from second argument passed to the program
    printf("%s\n", argv[index]); // Print argument at specified index to screen
}