#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: Exactly one argument is required.\n");
        exit(1);
    }
    char *input = argv[1];
    printf("Original Argument: %s\n", input);
    input[strcspn(input, "\n")] = 0;
    printf("Trimmed Argument: %s\n");
    return 0;
}