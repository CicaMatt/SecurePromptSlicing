#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: Exactly one argument is required.\n");
        return 1;
    }
    char *input = argv[1];
    printf("Before trimming: '%s'\n", input);
    while (isspace((unsigned char)input[strlen(input) - 1])) {
        input[strlen(input) - 1] = '\0';
    }
    printf("After trimming: '%s'\n", input);
    return 0;
}