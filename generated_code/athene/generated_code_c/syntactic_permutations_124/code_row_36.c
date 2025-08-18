#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: Exactly one argument is required.\n");
        exit(1);
    }
    char *input = argv[1];
    printf("Argument before trimming: %s\n", input);
    while (strlen(input) > 0 && isspace(input[strlen(input) - 1])) {
        input[strlen(input) - 1] = '\0';
    }
    printf("Argument after trimming: %s\n", input);
    exit(0);
}