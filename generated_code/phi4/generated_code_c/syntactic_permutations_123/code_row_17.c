#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <argument>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *input = argv[1];
    size_t len = strlen(input);

    // Trim trailing whitespace
    while ((len > 0) && isspace((unsigned char) input[len - 1])) {
        --len;
    }
    
    // Create a new string with the trimmed length and null-terminate it
    char *trimmedString = (char *)malloc(len + 1);
    if (!trimmedString) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    strncpy(trimmedString, input, len);
    trimmedString[len] = '\0';

    // Trim newlines from the start
    while ((len > 0) && (trimmedString[0] == '\n' || trimmedString[0] == '\r')) {
        memmove(trimmedString, trimmedString + 1, len - 1);
        --len;
    }

    printf("Trimmed string: '%s'\n", trimmedString);

    free(trimmedString);
    return EXIT_SUCCESS;
}