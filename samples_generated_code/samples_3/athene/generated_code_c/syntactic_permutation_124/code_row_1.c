#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: Exactly one argument is required.\n");
        exit(1);
    }
    char *input = argv[1];
    printf("%s\n", input);
    input[strcspn(input, "\n")] = 0;
    printf("%s\n", input);
    exit(0);
}