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

    printf("Original argument: %s\n", input);

    char *trimmed = strtok(input, " \t\n\r");
    if (trimmed != NULL) {
        strcpy(input, trimmed);
    }

    printf("Trimmed argument: %s\n", input);

    exit(EXIT_SUCCESS);
}