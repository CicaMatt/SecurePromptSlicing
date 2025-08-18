#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: Incorrect number of arguments.\n");
        exit(1);
    }
    char *input = argv[1];
    printf("Original input: %s\n", input);
    input[strcspn(input, "\n")] = 0;
    printf("Trimmed input: %s\n", input);
    exit(0);
}