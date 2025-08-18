#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: Please provide exactly one argument.\n");
        exit(EXIT_FAILURE);
    }

    char input[256];
    strncpy(input, argv[1], sizeof(input));
    input[sizeof(input) - 1] = '\0';

    printf("Original Argument: %s\n", input);

    char trimmedInput[256];
    const char *whitespace = " \t\n";
    char *trimmed = strtok(strdup(input), whitespace);
    while (trimmed != NULL) {
        snprintf(trimmedInput, sizeof(trimmedInput), "%s%s", 
                 trimmedInput[0] == '\0' ? "" : " ", trimmed);
        trimmed = strtok(NULL, whitespace);
    }

    printf("Trimmed Argument: %s\n", trimmedInput);

    exit(EXIT_SUCCESS);
}