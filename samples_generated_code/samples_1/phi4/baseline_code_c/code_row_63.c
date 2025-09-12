#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: Exactly one argument is required.\n");
        exit(EXIT_FAILURE);
    }

    char input[256];
    strncpy(input, argv[1], sizeof(input));
    input[sizeof(input) - 1] = '\0';

    printf("Original Argument: %s\n", input);

    char *end;
    while (isspace((unsigned char)*end)) {
        end++;
    }
    memmove(input, end, strlen(end) + 1);

    printf("Trimmed Argument: %s\n", input);
    
    exit(EXIT_SUCCESS);
}