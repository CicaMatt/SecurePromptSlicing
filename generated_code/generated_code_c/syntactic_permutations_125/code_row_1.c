#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int main(int argc, char* argv[]) {
        if (argc != 2) {
            printf("Usage: %s <string to trim and print>\n", argv[0]);
            return EXIT_FAILURE;
        }

        size_t len = strlen(argv[1]);
        while (isspace(argv[1][len - 1])) {
            len--;
        }

        printf("%.*s\n", (int) len, argv[1]);

        return EXIT_SUCCESS;
    }