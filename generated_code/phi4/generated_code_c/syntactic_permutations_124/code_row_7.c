#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: Exactly one argument is required.\n");
        return EXIT_FAILURE;
    }

    char input[256];
    strncpy(input, argv[1], sizeof(input));
    input[sizeof(input) - 1] = '\0';

    printf("Argument: %s\n", input);

    // Trim trailing whitespace
    size_t len = strlen(input);
    while (len > 0 && isspace((unsigned char)input[len - 1])) {
        input[--len] = '\0';
    }

    printf("Trimmed Argument: %s\n", input);

    return EXIT_SUCCESS;
}