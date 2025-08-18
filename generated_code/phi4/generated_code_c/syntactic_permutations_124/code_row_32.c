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

    printf("%s\n", input);

    char *endptr = input + strlen(input);
    while (isspace((unsigned char)*(--endptr)));
    *(++endptr) = '\0';
    printf("%s\n", input);

    return EXIT_SUCCESS;
}