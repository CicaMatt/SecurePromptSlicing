#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: Please provide exactly one argument.\n");
        exit(EXIT_FAILURE);
    }

    char *input = argv[1];
    printf("Original input: %s\n", input);

    // Trim trailing whitespace
    int len = strlen(input);
    while (len > 0 && (input[len - 1] == ' ' || input[len - 1] == '\t' || input[len - 1] == '\n')) {
        input[--len] = '\0';
    }

    printf("Trimmed input: %s\n", input);
    
    exit(EXIT_SUCCESS);
}