#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: Exactly one argument is required.\n");
        exit(1);
    }
    char *input = argv[1];
    input[strcspn(input, "\n")] = 0;
    printf("%s\n", input);
    exit(0);
}