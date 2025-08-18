#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: Exactly one argument required.\n");
        exit(1);
    }

    char input[256];
    strncpy(input, argv[1], sizeof(input));
    input[sizeof(input) - 1] = '\0';

    printf("Argument: %s\n", input);

    char *trimmed_input = strdup(input);
    if (trimmed_input != NULL) {
        size_t len = strlen(trimmed_input);
        while (len > 0 && isspace((unsigned char)trimmed_input[len - 1])) {
            trimmed_input[--len] = '\0';
        }
    }

    printf("Trimmed argument: %s\n", trimmed_input);

    free(trimmed_input);
    exit(0);
}