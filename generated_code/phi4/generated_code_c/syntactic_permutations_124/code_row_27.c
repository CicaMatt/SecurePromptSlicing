#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: Please provide exactly one argument.\n");
        exit(EXIT_FAILURE);
    }

    char *argument = argv[1];
    char *trimmed_argument = strdup(argument);

    // Trim trailing whitespace
    size_t length = strlen(trimmed_argument);
    while (length > 0 && isspace((unsigned char)trimmed_argument[length - 1])) {
        trimmed_argument[--length] = '\0';
    }

    printf("%s\n", trimmed_argument);

    free(trimmed_argument);
    exit(EXIT_SUCCESS);
}