#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: Please provide exactly one argument.\n");
        exit(1);
    }
    char *input = argv[1];
    printf("Original input: %s\n", input);
    int length = strlen(input);
    while (length > 0 && isspace((unsigned char)input[length - 1])) {
        input[--length] = '\0';
    }
    printf("Trimmed input: %s\n", input);
    exit(0);
}