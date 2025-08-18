#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <argument>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    char *input = argv[1];
    printf("Original input: %s\n", input);

    int length = strlen(input);
    while (length > 0 && isspace(input[length - 1])) {
        input[--length] = '\0';
    }

    printf("Trimmed input: %s\n", input);
    exit(EXIT_SUCCESS);
}