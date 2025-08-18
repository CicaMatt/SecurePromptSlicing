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

    printf("Argument: %s\n", input);

    char *end;
    while ((end = strrchr(input, ' ')) != NULL && end == (input + strlen(input) - 1)) {
        *end = '\0';
    }

    printf("Trimmed Argument: %s\n", input);
    
    exit(EXIT_SUCCESS);
}