#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: Please provide exactly one argument.\n");
        exit(EXIT_FAILURE);
    }

    const char *input = argv[1];
    printf("Argument: %s\n", input);

    // Remove trailing dot
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '.') {
        char trimmed[len];
        strncpy(trimmed, input, len - 1);
        trimmed[len - 1] = '\0';
        printf("Trimmed: %s\n", trimmed);
    } else {
        printf("No trailing dot to remove.\n");
    }

    return 0;
}