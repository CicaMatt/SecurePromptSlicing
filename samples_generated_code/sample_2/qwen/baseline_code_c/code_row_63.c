#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: Please provide exactly one argument.\n");
        exit(EXIT_FAILURE);
    }
    char *input = argv[1];
    printf("Original input: %s\n", input);
    while (*input && isspace((unsigned char)*input)) input++;
    char *end = input + strlen(input) - 1;
    while (end > input && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0';
    printf("Trimmed input: %s\n", input);
    exit(EXIT_SUCCESS);
}