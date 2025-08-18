#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARG_LENGTH 256

void trimTrailingWhitespace(char *str) {
    char *end;

    while (*str) str++; // Move to the end of the string
    end = str - 1;      // Set end at the last character

    // Trim trailing whitespace characters
    while (end >= str && (*end == ' ' || *end == '\t' || *end == '\n')) {
        *end-- = '\0';
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: Exactly one argument is required.\n");
        return EXIT_FAILURE;
    }

    char arg[MAX_ARG_LENGTH];
    strncpy(arg, argv[1], MAX_ARG_LENGTH - 1);
    arg[MAX_ARG_LENGTH - 1] = '\0'; // Ensure null-termination

    trimTrailingWhitespace(arg);

    printf("%s\n", arg);

    return EXIT_SUCCESS;
}