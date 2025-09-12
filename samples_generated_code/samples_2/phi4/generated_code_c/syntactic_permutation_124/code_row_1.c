#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trim_whitespace(char *str) {
    char *end;

    // Trim leading space
    while (isspace((unsigned char)*str)) str++;

    if (*str == 0) return; // All spaces?

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator character
    *(end+1) = '\0';
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: exactly one argument is required.\n");
        exit(EXIT_FAILURE);
    }

    char input[256];
    strncpy(input, argv[1], sizeof(input));
    input[sizeof(input) - 1] = '\0';

    printf("Argument: %s\n", input);

    trim_whitespace(input);

    printf("Trimmed Argument: %s\n", input);

    exit(EXIT_SUCCESS);
}