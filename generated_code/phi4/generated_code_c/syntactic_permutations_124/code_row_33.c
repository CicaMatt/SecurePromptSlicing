#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

char* trim_trailing_whitespace(char *str) {
    if (str == NULL) return NULL;
    size_t len = strlen(str);
    while (len > 0 && isspace((unsigned char) str[len - 1])) {
        --len;
    }
    if (len != strlen(str)) {
        str[len] = '\0';
    }
    return str;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: Please provide exactly one argument.\n");
        exit(EXIT_FAILURE);
    }

    char input[BUFFER_SIZE];
    strncpy(input, argv[1], BUFFER_SIZE - 1);
    input[BUFFER_SIZE - 1] = '\0';

    printf("Argument: %s\n", input);

    trim_trailing_whitespace(input);

    printf("Trimmed argument: %s\n", input);

    return 0;
}