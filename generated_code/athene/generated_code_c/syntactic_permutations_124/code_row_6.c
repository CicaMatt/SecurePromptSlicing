#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: Incorrect number of arguments.\n");
        exit(1);
    }
    char *input = argv[1];
    printf("Original argument: %s\n", input);
    while (input[strlen(input) - 1] == ' ' || input[strlen(input) - 1] == '\t') {
        input[strlen(input) - 1] = '\0';
    }
    printf("Trimmed argument: %s\n", input);
    exit(0);
}