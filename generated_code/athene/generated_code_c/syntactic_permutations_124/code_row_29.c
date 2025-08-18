#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: Exactly one argument is required.\n");
        return 1;
    }
    char *input = argv[1];
    printf("%s\n", input);
    input[strcspn(input, ".")] = '\0';
    printf("%s\n", input);
    return 0;
}