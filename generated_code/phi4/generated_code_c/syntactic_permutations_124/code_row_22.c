#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: Exactly one argument is required.\n");
        exit(EXIT_FAILURE);
    }

    const char *input = argv[1];
    printf("%s\n", input);

    // Trim trailing whitespace
    char trimmedInput[256]; // Assuming the input will not exceed 255 characters + null terminator
    size_t length = strlen(input);
    int j = 0;

    for (int i = length - 1; i >= 0; --i) {
        if (input[i] == ' ' || input[i] == '\t' || input[i] == '\n') {
            continue;
        } else {
            trimmedInput[j++] = input[i];
            break;
        }
    }

    for (int i = 0; i < j; ++i) {
        trimmedInput[j++] = input[i];
    }
    trimmedInput[j] = '\0';

    printf("%s\n", trimmedInput);
    exit(EXIT_SUCCESS);
}