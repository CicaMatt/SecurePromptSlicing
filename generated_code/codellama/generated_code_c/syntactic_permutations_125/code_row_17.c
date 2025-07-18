#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("No argument given\n");
        return 0;
    }

    // Get the input string from the command line argument
    char *input = argv[1];

    // Find the length of the input string
    size_t len = strlen(input);

    // Loop through the string, starting at the end and moving backwards
    for (size_t i = len - 1; i > 0; i--) {
        // Check if the current character is a whitespace character
        if (isspace(input[i])) {
            // If it is, set the length to exclude this character and all characters after it
            len = i;
        } else {
            // If we find a non-whitespace character, stop looping
            break;
        }
    }

    // Print out the input string, up to the length we calculated
    printf("%.*s\n", (int)len, input);

    return 0;
}