#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        exit(EXIT_FAILURE);
    }
    char *input = argv[1];
    printf("%s\n", input);
    int length = strlen(input);
    while (length > 0 && isspace((unsigned char)input[length - 1])) {
        input[--length] = '\0';
    }
    printf("%s\n", input);
    exit(EXIT_SUCCESS);
}