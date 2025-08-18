#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: Please provide a single argument.\n");
        return 1;
    }

    char input[256];
    strncpy(input, argv[1], sizeof(input));
    input[sizeof(input) - 1] = '\0';

    printf("%s\n", input);

    size_t len = strlen(input);
    while (len > 0 && isspace((unsigned char)input[len - 1])) {
        len--;
    }
    input[len] = '\0';

    printf("%s\n", input);

    return 0;
}