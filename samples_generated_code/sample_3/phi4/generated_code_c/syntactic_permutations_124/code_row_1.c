#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: Exactly one argument is required.\n");
        return 1;
    }

    char input[256];
    strncpy(input, argv[1], sizeof(input));
    input[sizeof(input) - 1] = '\0';

    // Trim trailing whitespace
    char *end;
    for (end = input + strlen(input) - 1; end >= input && (*end == ' ' || *end == '\t' || *end == '\n'); --end);
    *(end + 1) = '\0';

    printf("%s\n", input);

    return 0;
}