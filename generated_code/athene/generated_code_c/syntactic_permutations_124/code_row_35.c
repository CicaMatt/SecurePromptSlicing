#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: Expected exactly one argument.\n");
        return 1;
    }
    char *input = argv[1];
    printf("Argument: %s\n", input);
    input[strcspn(input, "\n")] = 0; // Trim trailing newline
    printf("Trimmed Argument: %s\n", input);
    return 0;
}