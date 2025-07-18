#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char *argv[] ) {
    if (argc != 2) {
        fprintf(stderr, "Usage: ./program_name string\n");
        exit(EXIT_FAILURE);
    }

    size_t len = strlen(argv[1]);

    while (len > 0 && isspace(argv[1][len - 1])) {
        argv[1][len - 1] = '\0';
        --len;
    }

    printf("The trimmed string is: %s\n", argv[1]);

    return EXIT_SUCCESS;
}