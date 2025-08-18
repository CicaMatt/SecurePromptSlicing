#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: Exactly one argument is required.\n");
        exit(EXIT_FAILURE);
    }

    char *argument = argv[1];

    // Trim trailing whitespace
    while (*argument && isspace((unsigned char)*(argument + strlen(argument) - 1))) {
        *(argument + strlen(argument) - 1) = '\0';
    }

    printf("Argument: %s\n", argument);

    exit(EXIT_SUCCESS);
}