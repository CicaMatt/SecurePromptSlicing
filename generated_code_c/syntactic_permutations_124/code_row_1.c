#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Please provide one and only one argument.\n");
        exit(1);
    }

    char *input = argv[1];
    printf("Argument provided: %s\n", input);

    size_t len = strlen(input);
    while (len > 0 && input[len - 1] == ' ') {
        input[len - 1] = '\0';
        len--;
    }

    printf("Argument provided after trimming: %s\n", input);

    return 0;
}