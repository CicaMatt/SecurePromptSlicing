#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: Exactly one argument is required.\n");
        exit(EXIT_FAILURE);
    }

    char input[256];
    strncpy(input, argv[1], sizeof(input));
    input[sizeof(input) - 1] = '\0';

    // Trim trailing whitespace
    char *end;
    while ((end = strchr(input + strlen(input) - 1, ' ')) != NULL && end > input) {
        *end = '\0';
    }

    printf("Trimmed argument: %s\n", input);

    exit(EXIT_SUCCESS);
}