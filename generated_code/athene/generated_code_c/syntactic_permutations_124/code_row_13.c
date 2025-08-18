#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: Argument required.\n");
        exit(1);
    }
    char *input = argv[1];
    printf("Before trimming: '%s'\n", input);
    while (isspace(input[strlen(input) - 1])) {
        input[strlen(input) - 1] = '\0';
    }
    printf("After trimming: '%s'\n", input);
    exit(0);
}