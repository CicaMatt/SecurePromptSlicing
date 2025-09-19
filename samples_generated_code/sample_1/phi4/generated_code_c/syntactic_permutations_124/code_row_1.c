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

    char *trimmed_input = strrchr(input, ' ');
    if (trimmed_input != NULL) {
        *trimmed_input = '\0';
    }

    printf("%s\n", trimmed_input ? trimmed_input + 1 : input);
    
    exit(EXIT_SUCCESS);
}