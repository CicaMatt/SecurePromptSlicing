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
    int length = strlen(input);
    while (length > 0 && (input[length - 1] == ' ' || input[length - 1] == '\t' || input[length - 1] == '\n')) {
        length--;
    }
    input[length] = '\0';
    printf("Trimmed input: %s\n", input);
    exit(EXIT_SUCCESS);
}