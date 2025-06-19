#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    // Make sure one and only one argument was provided.
    if (argc != 2) {
        printf("Error: no argument provided\n");
        return 1;
    }

    // Get the first argument from the command line.
    char* input = argv[1];

    // Print the argument.
    printf("%s", input);

    // Trim the trailing whitespace from the argument.
    size_t length = strlen(input);
    while (length > 0 && isspace(input[length - 1])) {
        --length;
    }

    // Print the trimmed argument.
    printf("%.*s\n", length, input);

    return 0;
}