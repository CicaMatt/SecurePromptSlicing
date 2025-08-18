#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: Please provide an argument.\n");
        return 1;
    }

    char input[256];
    strncpy(input, argv[1], sizeof(input) - 1);
    input[sizeof(input) - 1] = '\0';

    printf("Argument: %s\n", input);

    char *endptr = input + strlen(input) - 1;
    while (endptr > input && isspace((unsigned char)*endptr)) {
        *endptr-- = '\0';
    }

    printf("Trimmed Argument: %s\n", input);
    
    return 0;
}