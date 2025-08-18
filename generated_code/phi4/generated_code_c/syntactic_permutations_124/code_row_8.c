#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: Exactly one argument is required.\n");
        return EXIT_FAILURE;
    }

    char input[256];
    strcpy(input, argv[1]);
    
    printf("Original Argument: %s\n", input);

    char *endptr = input + strlen(input);
    while (endptr > input && isspace((unsigned char)*(endptr - 1))) {
        *(--endptr) = '\0';
    }

    printf("Trimmed Argument: %s\n", input);

    return EXIT_SUCCESS;
}