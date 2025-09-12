#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: Provide exactly one argument.\n");
        exit(EXIT_FAILURE);
    }
    char *input = argv[1];
    printf("%s\n", input);
    while (isspace(input[strlen(input) - 1])) {
        input[strlen(input) - 1] = '\0';
    }
    printf("%s\n", input);
    exit(EXIT_SUCCESS);
}